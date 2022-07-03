#include "../src/lights.h"
#include "../src/utils_colors.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPISLON 0.00001

Test(light, a_point_light_has_a_position_and_intensity) {
  t_color c = color(1, 1, 1);
  t_point position = point(0, 0, 0);
  t_light *light = point_light(c, position);
  for (int i = 0; i < 4; i++) {
    cr_assert_float_eq(light->position[i], position[i], EPISLON);
    cr_assert_float_eq(light->intensity[i], c[i], EPISLON);
  }
}

Test(material, default_material) {
  struct s_material *m = material();
  struct s_material expected = {.c = color(1, 1, 1),
                                .ambient = 0.1,
                                .diffuse = 0.9,
                                .specular = 0.9,
                                .shininess = 200.};
  cr_assert_float_eq(m->shininess, expected.shininess, EPISLON);
  cr_assert_float_eq(m->ambient, expected.ambient, EPISLON);
  cr_assert_float_eq(m->diffuse, expected.diffuse, EPISLON);
  cr_assert_float_eq(m->specular, expected.specular, EPISLON);
  for (int i = 0; i < 4; i++)
    cr_assert_float_eq(m->c[i], expected.c[i], EPISLON);
  destroy_material(&m);
  free(expected.c);
}

static t_vector eyev, normalv;
static struct s_material *m;
static t_light *light;
static t_color result, expected;
static t_point posi;

void init_lighting(void) {
	m = material();
	posi = point(0, 0, 0);
}

void fini_lighting(void) {
  free(eyev);
  free(normalv);
  destroy_material(&m);
  destroy_light(&light);
  free(result);
  free(expected);
  expected = NULL;
  result = NULL;
  eyev = NULL;
  normalv = NULL;
  m = NULL;
  light = NULL;
}

Test(lighting, lighting_with_the_eye_between_the_light_and_the_surface,
     .init = init_lighting, .fini = fini_lighting) {
	eyev = vector(0, 0, -1);
	normalv = vector(0, 0, -1);
	light = point_light(color(1, 1, 1), point(0, 0, -10));
	result = lighting(m, light, posi, (t_vector []){eyev, normalv});
	expected = color(1.9, 1.9, 1.9);
	for (int i = 0; i < 3; i++)
		cr_assert_float_eq(result[i], expected[i], EPISLON);
}

Test(lighting, lighting_with_the_eye_between_the_light_and_the_surface_eye_offtset_45_degress,
		.init=init_lighting, .fini=fini_lighting)
{
	eyev = vector(0, M_SQRT2 / 2., -M_SQRT2 / 2.);
	normalv = vector(0, 0, -1);
	light = point_light(color(1, 1, 1), point(0, 0, -10));
	result = lighting(m, light, posi, (t_vector []){eyev, normalv});
	expected = color(1, 1, 1);
	for (int i = 0; i < 3; i++)
		cr_assert_float_eq(result[i], expected[i], EPISLON);
}

Test(lighting, lighting_with_eye_opposite_surface_light_offset_45_degress,
		.init=init_lighting, .fini=fini_lighting)
{
	eyev = vector(0, 0, -1);
	normalv = vector(0, 0, -1);
	light = point_light(color(1, 1, 1), point(0, 10, -10));
	result = lighting(m, light, posi, (t_vector []){eyev, normalv});
	expected = color(0.7364, 0.7364, 0.7364);
	for (int i = 0; i < 3; i++)
		cr_assert_float_eq(result[i], expected[i], EPISLON);
}

#define SQRT2_2 M_SQRT2 / 2.

Test(lighting, lighting_with_eye_in_the_path_of_the_reflection_vector,
		.init=init_lighting, .fini=fini_lighting)
{
	eyev = vector(0, -SQRT2_2, -SQRT2_2);
	normalv = vector(0, 0, -1);
	light = point_light(color(1, 1, 1), point(0, 10, -10));
	result = lighting(m, light, posi, (t_vector []){eyev, normalv});
	expected = color(1.6364, 1.6364, 1.6364);
	for (int i = 0; i < 3; i++)
		cr_assert_float_eq(result[i], expected[i], EPISLON);
}

Test(lighting, lighting_with_light_behind_the_surface,
		.init=init_lighting, .fini=fini_lighting)
{
	eyev = vector(0, 0, -1);
	normalv = vector(0, 0, -1);
	light = point_light(color(1, 1, 1), point(0, 0, 10));
	result = lighting(m, light, posi, (t_vector []){eyev, normalv});
	expected = color(0.1, 0.1, 0.1);
	for (int i = 0; i < 3; i++)
		cr_assert_float_eq(result[i], expected[i], EPISLON);
}
