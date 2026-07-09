/* ************************************************************************** */
/*                                                                            */
/*                              TEST BENCH                                    */
/*                                                                            */
/*   Not graded, not part of the mandatory build (see subject: tests are     */
/*   encouraged but not submitted). Build and run from the repo root:        */
/*                                                                            */
/*       make test && ./test_parsing                                          */
/*                                                                            */
/*   Covers the fixes made so far:                                            */
/*     step 1: dispatcher passes the full line to parsers                     */
/*     step 2: line endings stripped (\n, \r, missing final newline)          */
/*     step 3: errors propagate, parsing stops at first error                 */
/*     step 4: no leaks on any parser error path (run under valgrind)         */
/*     step 5: sous_vec returns a - b                                         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	g_fail = 0;

static int	feq(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

static int	ceq(t_color c, int r, int g, int b)
{
	return (feq(c.x, r / 255.0) && feq(c.y, g / 255.0)
		&& feq(c.z, b / 255.0));
}

static void	check(int cond, char *name)
{
	if (cond)
		printf("  [OK] %s\n", name);
	else
	{
		printf("  [KO] %s\n", name);
		g_fail++;
	}
}

static void	test_parsers(void)
{
	t_scene	s;

	printf("--- element parsers ---\n");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("A 0.2 255,128,0", &s) == 1
		&& feq(s.ambient.ratio, 0.2) && ceq(s.ambient.color, 255, 128, 0),
		"ambient: valid line accepted, values stored");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("A 1.5 255,255,255", &s) == 0, "ambient: bad ratio");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("A 0.2 300,0,0", &s) == 0, "ambient: bad RGB");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("C -50.0,0,20 0,0,1 70", &s) == 1
		&& feq(s.camera.position.x, -50.0) && feq(s.camera.fov, 70.0),
		"camera: valid line accepted, values stored");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("C 0,0,0 2,0,0 70", &s) == 0, "camera: dir > 1");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("C 0,0,0 1,2 70", &s) == 0,
		"camera: dir with 2 values (step 4 leak path)");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("C 0,0,0 0,0,1 999", &s) == 0, "camera: bad FOV");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("L -40.0,50.0,0.0 0.6 10,20,30", &s) == 1
		&& feq(s.light.position.y, 50.0) && ceq(s.light.color, 10, 20, 30),
		"light: valid line accepted, values stored");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("L 0,0,0 0.5", &s) == 0, "light: truncated");
}

static void	test_duplicates(void)
{
	t_scene	s;

	printf("--- duplicate elements ---\n");
	ft_bzero(&s, sizeof(t_scene));
	parse_line("A 0.2 255,255,255", &s);
	check(parse_line("A 0.3 0,0,0", &s) == 0, "second A rejected");
	ft_bzero(&s, sizeof(t_scene));
	parse_line("C 0,0,0 0,0,1 70", &s);
	check(parse_line("C 1,1,1 0,1,0 90", &s) == 0, "second C rejected");
	ft_bzero(&s, sizeof(t_scene));
	parse_line("L 0,0,0 0.5 255,255,255", &s);
	check(parse_line("L 1,1,1 0.2 0,0,0", &s) == 0, "second L rejected");
}

static void	test_dispatcher(void)
{
	t_scene	s;

	printf("--- dispatcher ---\n");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("   A 0.2 255,255,255", &s) == 1,
		"leading spaces skipped");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("# comment", &s) == 1, "comment ignored");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("", &s) == 1, "empty line ignored");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_line("X 1,2,3", &s) == 0, "unknown identifier rejected");
}

static void	test_files(void)
{
	t_scene	s;

	printf("--- parse_file ---\n");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_file("scenes/test.rt", &s) == 1
		&& s.ambient_set && s.camera_set
		&& s.light_set,
		"valid scene: returns 1, all elements set");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_file("scenes/test_crlf_noeol.rt", &s) == 1,
		"CRLF scene without final newline parsed");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_file("scenes/err_then_valid.rt", &s) == 0
		&& s.camera_set == 0,
		"broken scene: returns 0, parsing stopped at first error");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_file("scenes/unknown_id.rt", &s) == 0,
		"unknown identifier in file rejected");
	ft_bzero(&s, sizeof(t_scene));
	check(parse_file("scenes/nope.rt", &s) == 0, "missing file rejected");
}

static void	test_object_list(void)
{
	t_scene		s;
	t_object	blue;
	t_object	*node;

	printf("--- object list ---\n");
	ft_bzero(&s, sizeof(t_scene));
	ft_bzero(&blue, sizeof(t_object));
	blue.type = SPHERE;
	blue.color = (t_color){1.0, 0.0, 0.0};
	blue.shape.sphere = (t_sphere){(t_vector){0, 0, 5}, 1.5};
	node = add_object(&s, blue);
	check(node != NULL && s.objects == node,
		"first object becomes list head");
	blue.type = PLANE;
	blue.shape.plane = (t_plane){(t_vector){0, -1, 0}, (t_vector){0, 1, 0}};
	node = add_object(&s, blue);
	check(s.objects->next == node && node->next == NULL,
		"second object appended at tail");
	check(s.objects->type == SPHERE && s.objects->next->type == PLANE,
		"tags preserved in file order");
	check(feq(s.objects->shape.sphere.radius, 1.5)
		&& feq(s.objects->next->shape.plane.normal.y, 1.0),
		"union payloads read back through the right tag");
	free_objects(&s);
	check(s.objects == NULL, "free_objects resets the head");
	free_objects(&s);
	check(1, "double free_objects is harmless");
}

static void	test_vectors(void)
{
	t_vector	a;
	t_vector	b;
	t_vector	r;

	printf("--- vectors ---\n");
	a = (t_vector){5.0, 3.0, 1.0};
	b = (t_vector){1.0, 1.0, 1.0};
	r = sous_vec(a, b);
	check(r.x == 4.0 && r.y == 2.0 && r.z == 0.0,
		"sous_vec(a, b) == a - b");
	a = (t_vector){0.0, 0.0, 0.0};
	b = (t_vector){0.0, 0.0, 5.0};
	r = sous_vec(a, b);
	check(r.z == -5.0, "oc = origin - center points backward");
}

int	main(void)
{
	printf("========== MINI RT TEST BENCH ==========\n");
	test_parsers();
	test_duplicates();
	test_dispatcher();
	test_files();
	test_object_list();
	test_vectors();
	printf("========================================\n");
	if (g_fail == 0)
		printf("ALL TESTS PASSED\n");
	else
		printf("%d TEST(S) FAILED\n", g_fail);
	return (g_fail != 0);
}