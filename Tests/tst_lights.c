#include "../src/lights.h"
#include "../src/utils_colors.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/tuples_utils.h"
#include "../src/raycast.h"
#include "../src/miniRT.h"
#include <math.h>

#define EPISLON 0.00001

static void	destroy_used_memory(struct s_utils_lighting *util)
{
	free(util->ambient);
	free(util->diffuse);
	free(util->effective_color);
	free(util->specular);
	free(util->left);
	free(util->right);
}

static void	init_variables(struct s_utils_lighting *util, t_light *light,
		struct s_material *material)
{
	util->left = NULL;
	util->right = NULL;
	util->light_dot_normal = 0;
	util->reflect_dot_eye = 0;
	util->effective_color = color(
			light->intensity[0] * material->c[0],
			light->intensity[1] * material->c[1],
			light->intensity[2] * material->c[2]
			);
	util->ambient = scalar_multiplication(util->effective_color, material->ambient);
	util->diffuse = color(0, 0, 0);
	util->specular = color(0, 0, 0);
}

static inline t_color	lighting_(
		struct s_material *m,
		t_light	*l,
		t_point position, t_vector eye_normalv[2])
{
	struct s_utils_lighting	util;
	t_vector	tmp;
	t_color		result;

	init_variables(&util, l, m);
	tmp = sub_tuple(l->position, position);
	util.left = normalize(tmp);
	util.light_dot_normal = dot_product(util.left, eye_normalv[1]);
	if (free(tmp), util.light_dot_normal >= 0)
	{
		free(util.diffuse);
		util.diffuse = scalar_multiplication(util.effective_color, m->diffuse * util.light_dot_normal);
		tmp = negate_tuple(util.left);
		util.right = reflect(tmp, eye_normalv[1]);
		util.reflect_dot_eye = dot_product(util.right, eye_normalv[0]);
		if (util.reflect_dot_eye > 0)
		{
			free(util.specular);
			util.specular = scalar_multiplication(l->intensity,
					powf(util.reflect_dot_eye, m->shininess) * m->specular);
		}
	}
	tmp = add_tuples(util.ambient, util.diffuse);
	result = add_tuples(tmp, util.specular);
	return (free(tmp), destroy_used_memory(&util), result);
}

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

static void init_lighting(void) {
	m = material();
	posi = point(0, 0, 0);
}

static void fini_lighting(void) {
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
	result = lighting_(m, light, posi, (t_vector []){eyev, normalv});
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
	result = lighting_(m, light, posi, (t_vector []){eyev, normalv});
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
	result = lighting_(m, light, posi, (t_vector []){eyev, normalv});
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
	result = lighting_(m, light, posi, (t_vector []){eyev, normalv});
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
	result = lighting_(m, light, posi, (t_vector []){eyev, normalv});
	expected = color(0.1, 0.1, 0.1);
	for (int i = 0; i < 3; i++)
		cr_assert_float_eq(result[i], expected[i], EPISLON);
}
