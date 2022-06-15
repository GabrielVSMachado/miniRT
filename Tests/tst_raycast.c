#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/raycast.h"
#include "../src/sphere.h"

# define  EPISLON 0.00001

static t_ray	*r;

void init_position(void)
{
	r = ray(point(2, 3, 4), vector(1, 0, 0));
}

void finish(void)
{
	destroy_ray(&r);
	r = NULL;
}


Test(ray, try_create_a_ray, .init=init_position, .fini=finish)
{
	cr_assert_not_null(r);
}

Test(position, expected_position_2_3_4, .init=init_position, .fini=finish) {
	t_point	result = position(r, 0);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], r->origin[i], EPISLON);
	}
}

Test(position, expected_position_3_3_4, .init=init_position, .fini=finish)
{
	t_point result = position(r, 1);
	t_point	expected_value = point(3, 3, 4);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
	}
}	

Test(position, expected_position_1_3_4, .init=init_position, .fini=finish)
{
	t_point	result = position(r, -1);
	t_point	expected_value =	point(1, 3, 4);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
	}
}

Test(position, expected_position_4f5_3_4, .init=init_position, .fini=finish){
	t_point	result = position(r, 2.5);
	t_point	expected_value =	point(4.5, 3, 4);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], expected_value[i], EPISLON);
	}
}

static	t_sphere	*s;

void	init_intersect(void){
	s = sphere();
}

void	finish_intersect(void) {
	free(s);
	destroy_ray(&r);
}

Test(intersect, expected_values_4_and_6_in_struct_xs, .init=init_intersect,.fini=finish_intersect){
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_xs	*result = intersect(s, r);
	cr_assert_eq(result->count, 2);
	cr_assert_float_eq(result->psec[0], 4.0, EPISLON);
	cr_assert_float_eq(result->psec[1], 6.0, EPISLON);
	free(result);
}

Test(intersect, ray_instersects_a_sphere_at_a_tangent, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 1, -5), vector(0, 0, 1));
	t_xs	*result = intersect(s, r);
	cr_assert_eq(result->count, 1);
	cr_assert_float_eq(result->psec[0], 5.0, EPISLON);
	cr_assert_float_eq(result->psec[1], 5.0, EPISLON);
	free(result);
}

Test(intersect, ray_misses_a_sphere, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 2, -5), vector(0, 0, 1));
	t_xs	*result = intersect(s, r);
	cr_assert_null(result);
	free(result);
}

Test(intersect, ray_originates_inside_a_sphere, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_xs	*result = intersect(s, r);
	cr_assert_float_eq(result->psec[0], -1.0, EPISLON);
	cr_assert_float_eq(result->psec[1], 1.0, EPISLON);
	free(result);
}

Test(intersect, ray_originates_after_a_sphere, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 0, 5), vector(0, 0, 1));
	t_xs	*result = intersect(s, r);
	cr_assert_float_eq(result->psec[0], -6.0, EPISLON);
	cr_assert_float_eq(result->psec[1], -4.0, EPISLON);
	free(result);
}
