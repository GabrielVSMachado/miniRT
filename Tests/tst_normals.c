#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdlib.h>
#include "../src/objects/object.h"
#include <math.h>

#define EPISLON 0.00001

static t_obj		*s;
static t_vector		expected_value;
static t_point		p;

void	init_normal(void) {
	s = new_object(SPHERE);
	s->inversed_transform = inverse(s->transform);
}

void	fini_normal(void) {
	destroy_object(&s);
	free(expected_value);
	free(p);
	p = NULL;
	expected_value = NULL;
	s = NULL;
}

Test(normal, expected_the_normal_vector_at_given_point_on_x_axis, .init=init_normal, .fini=fini_normal) {
	p = point(1, 0, 0);
	expected_value = vector(1, 0, 0);
	t_vector	result = normal_at(s, p);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}

Test(normal, expected_the_normal_vector_at_given_point_on_y_axis, .init=init_normal, .fini=fini_normal) {
	p = point(0, 1, 0);
	expected_value = vector(0, 1, 0);
	t_vector result = normal_at(s, p);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}

Test(normal, expected_the_normal_vector_at_given_point_on_z_axis, .init=init_normal, .fini=fini_normal) {
	p = point(0, 0, 1);
	expected_value = vector(0, 0, 1);
	t_vector result = normal_at(s, p);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}

#define SQRT3 sqrtf(3)

Test(normal, expected_the_normal_vector_at_nonaxial_given_point,.init=init_normal, .fini=fini_normal) {
	p = point(SQRT3, SQRT3, SQRT3);
	expected_value = vector(SQRT3, SQRT3, SQRT3);
	t_vector result = normal_at(s, p);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}

Test(normal, the_normal_is_a_normalized_vector, .init=init_normal, .fini=fini_normal) {
	p = point(SQRT3, SQRT3, SQRT3);
	t_vector result = normal_at(s, p);
	expected_value = normalize(result);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}

Test(normal, compute_the_normal_on_a_translated_sphere, .init=init_normal, .fini=fini_normal) {
	p = point(0, 1.70711, -0.70711);
	calc_linear_transformation(s, translate(0, 1, 0));
	free(s->inversed_transform);
	s->inversed_transform = inverse(s->transform);
	t_vector result = normal_at(s, p);
	expected_value = vector(0, 0.70711, -0.70711);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}

Test(normal, compute_the_normal_on_a_translated_sphere_2, .init=init_normal, .fini=fini_normal) {
	p = point(0, M_SQRT2 / 2., -M_SQRT2 / 2.);
	t_matrix *t = matrices_product(scale(1, 0.5, 1), rotation_z(M_PI / 5.));
	calc_linear_transformation(s, t);
	free(s->inversed_transform);
	s->inversed_transform = inverse(s->transform);
	t_vector result = normal_at(s, p);
	expected_value = vector(0, 0.97014, -0.24254);
	for (int i = 0; i < 0; i++)
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
}
