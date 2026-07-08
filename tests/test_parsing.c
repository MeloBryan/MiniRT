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
	t_data	d;

	printf("--- element parsers ---\n");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("A 0.2 255,128,0", &d) == 1
		&& d.ambient_ratio == 0.2 && d.ambient_color == 0xFF8000,
		"ambient: valid line accepted, values stored");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("A 1.5 255,255,255", &d) == 0, "ambient: bad ratio");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("A 0.2 300,0,0", &d) == 0, "ambient: bad RGB");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("C -50.0,0,20 0,0,1 70", &d) == 1
		&& d.cam_pos.x == -50.0 && d.cam_fov == 70.0,
		"camera: valid line accepted, values stored");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("C 0,0,0 2,0,0 70", &d) == 0, "camera: dir > 1");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("C 0,0,0 1,2 70", &d) == 0,
		"camera: dir with 2 values (step 4 leak path)");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("C 0,0,0 0,0,1 999", &d) == 0, "camera: bad FOV");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("L -40.0,50.0,0.0 0.6 10,20,30", &d) == 1
		&& d.light_pos.y == 50.0 && d.light_color == 0x0A141E,
		"light: valid line accepted, values stored");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("L 0,0,0 0.5", &d) == 0, "light: truncated");
}

static void	test_duplicates(void)
{
	t_data	d;

	printf("--- duplicate elements ---\n");
	ft_bzero(&d, sizeof(t_data));
	parse_line("A 0.2 255,255,255", &d);
	check(parse_line("A 0.3 0,0,0", &d) == 0, "second A rejected");
	ft_bzero(&d, sizeof(t_data));
	parse_line("C 0,0,0 0,0,1 70", &d);
	check(parse_line("C 1,1,1 0,1,0 90", &d) == 0, "second C rejected");
	ft_bzero(&d, sizeof(t_data));
	parse_line("L 0,0,0 0.5 255,255,255", &d);
	check(parse_line("L 1,1,1 0.2 0,0,0", &d) == 0, "second L rejected");
}

static void	test_dispatcher(void)
{
	t_data	d;

	printf("--- dispatcher ---\n");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("   A 0.2 255,255,255", &d) == 1,
		"leading spaces skipped");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("# comment", &d) == 1, "comment ignored");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("", &d) == 1, "empty line ignored");
	ft_bzero(&d, sizeof(t_data));
	check(parse_line("X 1,2,3", &d) == 0, "unknown identifier rejected");
}

static void	test_files(void)
{
	t_data	d;

	printf("--- parse_file ---\n");
	ft_bzero(&d, sizeof(t_data));
	check(parse_file("scenes/test.rt", &d) == 1
		&& d.ambient_already_set && d.camera_already_set
		&& d.light_already_set,
		"valid scene: returns 1, all elements set");
	ft_bzero(&d, sizeof(t_data));
	check(parse_file("scenes/test_crlf_noeol.rt", &d) == 1,
		"CRLF scene without final newline parsed");
	ft_bzero(&d, sizeof(t_data));
	check(parse_file("scenes/err_then_valid.rt", &d) == 0
		&& d.camera_already_set == 0,
		"broken scene: returns 0, parsing stopped at first error");
	ft_bzero(&d, sizeof(t_data));
	check(parse_file("scenes/unknown_id.rt", &d) == 0,
		"unknown identifier in file rejected");
	ft_bzero(&d, sizeof(t_data));
	check(parse_file("scenes/nope.rt", &d) == 0, "missing file rejected");
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
	test_vectors();
	printf("========================================\n");
	if (g_fail == 0)
		printf("ALL TESTS PASSED\n");
	else
		printf("%d TEST(S) FAILED\n", g_fail);
	return (g_fail != 0);
}
