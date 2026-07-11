# miniRT — Project State & Roadmap (proto-README)

> Working document, milestone 5 (mandatory rendering complete: scene, intersections, camera, lighting).
> Will be trimmed into the final `README.md` required by the subject
> (first line with logins, Description / Instructions / Resources sections).

---

## 1. What is ray tracing?

There are two families of techniques to turn a 3D scene into a 2D image:

- **Rasterization** projects the geometry onto the screen and fills in
  triangles. It is what GPUs and game engines do — extremely fast, but
  lighting effects are approximations.
- **Ray tracing** works backwards from the eye: for every pixel of the
  image, it shoots a mathematical ray from the camera through that pixel
  into the scene, and asks "what does this ray hit first, and what color
  is that point?". It is slower but physically faithful: shadows,
  reflections and refractions come naturally from the model.

miniRT implements the simplest form of this idea. The pipeline for one
frame is:

```
for each pixel (x, y) of the window:
    1. build a ray:   origin = camera position
                      direction = through the pixel on a virtual screen
    2. intersect it against every object in the scene
    3. keep the CLOSEST hit (smallest positive distance t)
    4. compute the color at that point (ambient + diffuse light, shadows)
    5. write the pixel into the MLX image
then push the image to the window once.
```

The math never goes beyond high-school algebra: an intersection is
"plug the ray equation `P(t) = origin + t * direction` into the object
equation and solve for t" — a quadratic for spheres and cylinders, a
single division for planes.

---

## 2. What the program can do today

**Scene parsing (complete: A, C, L, sp, pl, cy):**
- Takes a `*.rt` scene file as its only argument; rejects any other
  usage, a missing file, or a wrong extension, with `Error\n` + message
  and exit code 1 (subject-compliant).
- Parses every mandatory element. The unique ones (capital letters):
  - `A` ambient light — ratio in [0.0, 1.0], RGB in [0, 255]
  - `C` camera — position, direction in [-1, 1] (non-zero), FOV in [0, 180]
  - `L` light — position, brightness ratio in [0.0, 1.0], RGB (unused in
    mandatory part but parsed and validated)

  And the repeatable objects (lowercase), stored as a linked list of
  tagged unions in t_scene, in file order:
  - `sp` sphere — center, diameter (> 0, stored as radius), color
  - `pl` plane — point, normal (validated, normalized on input), color
  - `cy` cylinder — center (axis midpoint), axis (normalized), diameter
    and height (> 0), color
  Directions share one helper (parse_direction): components in [-1,1],
  non-zero, normalized at parse time. Colors are stored normalized to
  [0.0, 1.0] as t_color (= t_vector); packed to 0xRRGGBB only at MLX
  write time. The subject's chapter IV example scene is a test fixture
  asserted value-for-value.
- Tolerates: blank lines, whitespace-only lines, leading spaces/tabs,
  multiple spaces between fields, `#` comment lines, Windows CRLF line
  endings, missing final newline.
- Rejects with a precise message: wrong token counts, out-of-range
  values, malformed triplets, duplicate A/C/L, unknown identifiers,
  scenes missing any of A/C/L. Parsing stops at the first error; the
  rest of the file is still read and freed (no leak).

**Rendering (prototype):**
- Opens an MLX window (1920x1080), renders into an MLX image, pushes it
  once (as the subject recommends).
- Real camera model: builds an orthonormal basis (forward/right/up) from
  the parsed camera direction and shoots one normalized ray per pixel,
  aspect-ratio correct.
- Ray/sphere intersection test via the quadratic discriminant, against
  ONE hardcoded sphere at (0,0,5) — pixels that hit are red, the rest
  show a direction-based gradient (a debug view that proves the rays
  sweep the screen correctly).
- ESC and the window's red cross both exit cleanly; window management
  stays fluid (event-driven MLX loop).

**Engineering:**
- 0 norminette errors across `src/`, `includes/` and `libft/`.
- 0 leaks (ASan/valgrind), including on every parser error path.
- Regression bench: `make test && ./test_parsing` — 23 checks covering
  every fix ever made, so none can silently come back.
- Makefile: no relinking, automatic header dependencies (`-MMD -MP`),
  `bonus` rule, robust MiniLibX build (library only, demos skipped).

---

## 3. What it cannot do yet (honest list)

- **No object transformations at runtime.** The subject requires
  translation/rotation of objects, lights and cameras; scenes are
  currently static once loaded (keys only close the window). Needs a
  key-handling + re-render pass.
- **FOV is parsed but ignored.** The virtual screen sits at a fixed
  distance, giving an implicit ~90° field of view whatever the file says.
- **Hit test is boolean.** The intersection returns hit/no-hit, not the
  distance `t`, so there is no notion of "closest object", no hit point,
  no surface normal.
- **No lighting.** Ambient ratio, light position and brightness are
  parsed and stored but never used; no diffuse shading, no shadows.
- **No object colors.** Everything that hits is plain red.
- **Camera edge case:** a camera pointing straight up or down (0,±1,0)
  is parallel to the world-up vector; the cross product degenerates and
  the basis becomes invalid (NaN). Known, to be fixed in the camera
  module.
- **Numeric validation is lenient.** `ft_atof("abc")` yields 0.0 and is
  accepted; strict "is this really a number" validation is planned.
- **No bonus features** (specular, checkerboard, multi-lights, cone,
  bump mapping).

---

## 4. Architecture

```
src/
 |-- main.c            entry point: usage check, parse, render, cleanup
 |-- Parsing/          .rt file -> validated t_data
 |     parse_line.c      file loop, line dispatcher
 |     parse_utils.c     shared: rt_error, parse_vec3, parse_rgb,
 |                        matrix_length, check_extension
 |     parse_ambient.c / parse_camera.c / parse_light.c
 |     free.c            free_data (MLX teardown), free_matrix
 |-- Vectors/          math toolbox: add, sub (a-b), mul, dot, cross,
 |                      length, normalization
 |-- Rayon/            ray_init (pixel -> world ray),
 |                      update_camera_vectors (camera basis, t_basis)
 |-- Image/            window_handler (MLX window + events),
 |                      renderer (pixel loop, hardcoded sphere test)
includes/              one header per module + structures.h (t_vector,
                        t_ray, t_basis, t_data)
tests/                 test bench (make test), not graded
scenes/                .rt fixtures: valid, CRLF, broken, incomplete
libft/                 personal C library (norm-checked at grading too)
```

Conventions established:
- Parsers return `int` (1 = ok, 0 = error) and every error goes through
  `rt_error(msg)`.
- Each `ft_split` result is owned and freed by the function that created
  it; helpers `parse_vec3` / `parse_rgb` encapsulate split + validate +
  free in one call.
- `sous_vec(a, b)` is `a - b`, matching every raytracing formula
  (`oc = origin - center`, `light_dir = light - hit`).

---

## 5. Foundation work log (milestone 1)

| # | Fix | Why it mattered |
|---|-----|-----------------|
| 1 | Dispatcher passed `line + 1` to parsers expecting the identifier | Every valid .rt line was rejected; file parsing was dead on arrival |
| 2 | Strip `\n` / `\r` from get_next_line output | Last token of every line was polluted; CRLF scenes broke |
| 3 | Parsers return int, errors propagate, parsing stops at first error | A broken scene must exit(1), not open a window; drain loop avoids GNL leak |
| 4 | `dir_tokens` leaked on one camera error path | Found and proven with ASan; all 21 error branches now swept leak-free |
| 5 | `sous_vec` returned `b - a` | Would have silently inverted geometry in all future intersection/lighting math |
| 6 | Makefile rebuilt | -lm misplaced, include typo, 3 vector files never compiled, `bonus` rule missing, MLX demo build could break `make re`; added dep tracking + `make test` |
| 7 | Full norminette pass (0 errors), real `main` | Extracted parse helpers, `t_basis` (5-param fix), per-pixel render split; also fixed a NULL-deref bug in libft's `ft_split_spaces` |

---

## 6. Build & test (Fedora)

```
sudo dnf install gcc make libX11-devel libXext-devel   # once
git clone https://github.com/42Paris/minilibx-linux.git minilibx_linux
make                     # builds libft, MLX (lib only), MiniRT
./MiniRT scenes/test.rt  # gradient + red sphere; ESC or red cross to quit
make test && ./test_parsing            # 23 regression checks
valgrind --leak-check=full ./MiniRT scenes/err_then_valid.rt
```

---

## 7. Roadmap — remaining modules

Estimates assume focused work, alone, with review of each formula (not
copy-paste speed). Ranges: low = things go smoothly, high = debugging.

| # | Module | Content | Estimate |
|---|--------|---------|----------|
| 1 | ~~**Objects: parsing & storage**~~ | DONE — t_scene, tagged-union list, sp/pl/cy parsers, parse_direction, 62-check bench incl. subject example | ~~4–6 h~~ |
| 2 | ~~**Intersections**~~ | DONE — t_hit/ray_at, sphere quadratic, plane, cylinder tube + caps, closest-hit loop, headless pixel-asserted renders, 95-check bench | ~~8–12 h~~ |
| 3 | ~~**Real camera**~~ | DONE — right-handed basis, horizontal FOV via tan(fov/2) precomputed in t_basis, vertical-camera fallback up, zoom pixel-asserted | ~~3–4 h~~ |
| 4 | ~~**Lighting**~~ | DONE — ambient + Lambert diffuse (white light per subject), interior normal flip at shading, hard shadows reusing hit_anything with the t < light_dist bound, pixel-exact tests | ~~6–8 h~~ |
| 5 | **Hardening** | Strict numeric validation (reject "abc", "1.2.3", empty fields); normalized-vector checks; fuzz the parser with hostile scenes; full valgrind pass on every scene | **3–4 h** |
| 6 | **Defense prep** | Scene set showcasing every feature and every error path; final README (subject chapter V: logins line, Description, Instructions, Resources + AI usage); dry-run explaining each formula | **2–3 h** |

**Mandatory total: roughly 26–37 hours of focused work.**

Bonus (only after the mandatory part is *perfect* — the subject ignores
bonuses otherwise):

| Bonus | Estimate |
|-------|----------|
| Specular reflection (full Phong) | 2–3 h |
| Checkerboard pattern | 2–3 h |
| Colored + multi-spot lights | 2–3 h |
| Second-degree object (cone) | 4–6 h |
| Bump map textures | 4–6 h |

---

## 8. Design calls pending (owner: you)

Before module 1 starts, three decisions shape everything downstream:

1. **Object storage** — linked list of generic `t_object` (type enum +
   union) vs fixed arrays per type. Recommendation: linked list — one
   traversal loop for closest-hit, no arbitrary caps, extends to the
   bonus cone for free.
2. **Scene struct** — introduce a clean `t_scene` (camera, ambient,
   light, objects) separate from the MLX-centric `t_data`, or keep
   growing `t_data`. Recommendation: `t_scene` now, while the move is
   cheap.
3. **Color representation** — packed `int` (current) vs `t_vector`
   per channel. Recommendation: `t_vector` — the lighting module
   multiplies colors by ratios constantly, and vector form makes that
   one `mul_vec` call instead of unpack/scale/clamp/repack.
