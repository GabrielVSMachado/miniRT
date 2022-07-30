#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/ray/raycast.h"

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

#include "../src/intersections/intersections.h"

static	t_obj	*s;
static struct s_intersect	*head;

void	init_intersect(void){
	s = new_object(SPHERE);
	s->inversed_transform = inverse(s->transform);
	head = NULL;
}

void	finish_intersect(void) {
	if (r)
		destroy_ray(&r);
	destroy_intersect(&head);
}

Test(intersect, expected_values_4_and_6_in_struct_xs, .init=init_intersect,.fini=finish_intersect){
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	add_back(&head, intersect(s, r));
	cr_assert_float_eq(head->t, 4.0, EPISLON);
	cr_assert_float_eq(head->next->t, 6.0, EPISLON);
}

Test(intersect, ray_instersects_a_sphere_at_a_tangent, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 1, -5), vector(0, 0, 1));
	add_back(&head, intersect(s, r));
	cr_assert_float_eq(head->t, 5.0, EPISLON);
	cr_assert_null(head->next);
}

Test(intersect, ray_misses_a_sphere, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 2, -5), vector(0, 0, 1));
	add_back(&head, intersect(s, r));
	cr_assert_null(head);
}

Test(intersect, ray_originates_inside_a_sphere, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	add_back(&head, intersect(s, r));
	cr_assert_float_eq(head->t, -1.0, EPISLON);
	cr_assert_float_eq(head->next->t, 1.0, EPISLON);
}

Test(intersect, ray_originates_after_a_sphere, .init=init_intersect, .fini=finish_intersect) {
	r = ray(point(0, 0, 5), vector(0, 0, 1));
	add_back(&head, intersect(s, r));
	cr_assert_float_eq(head->t, -6.0, EPISLON);
	cr_assert_float_eq(head->next->t, -4.0, EPISLON);
}

Test(intersections, expected_a_list_with_two_intersections,
		.init=init_intersect, .fini=finish_intersect) {
	t_obj	*s2 = new_object(SPHERE);
	s2->inversed_transform = inverse(s2->transform);
	add_back(&head, new_intersect(1.0, s));
	add_back(&head, new_intersect(2.5, s2));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

Test(hit, expected_the_first_value_of_the_list, .init=init_intersect, .fini=finish_intersect) {
	add_back(&head, new_intersect(1.0, s));
	add_back(&head, new_intersect(2.0, s));
	struct s_intersect	*result = hit(head);
	cr_assert_float_eq(result->t, 1.0, EPISLON);
}

Test(hit, expected_the_second_node_of_the_list, .init=init_intersect, .fini=finish_intersect) {
	add_back(&head, new_intersect(-1.0, s));
	add_back(&head, new_intersect(1.0, s));
	struct s_intersect	*result = hit(head);
	cr_assert_float_eq(result->t, 1.0, EPISLON);
}

Test(hit, expected_the_last_node_of_the_list, .init=init_intersect, .fini=finish_intersect) {
	add_back(&head, new_intersect(-1.0, s));
	add_back(&head, new_intersect(-2.0, s));
	struct s_intersect	*result = hit(head);
	cr_assert_null(result);
}

Test(hit, hit_the_lowest_non_negative, .init=init_intersect, .fini=finish_intersect) {
	add_back(&head, new_intersect(4.0, s));
	add_back(&head, new_intersect(5.0, s));
	add_back(&head, new_intersect(-1.0, s));
	add_back(&head, new_intersect(3.0, s));
	struct s_intersect	*result = hit(head);
	cr_assert_float_eq(result->t, 3.0, EPISLON);
}

static t_ray	*r;

void	init_raytranform(void) {
	r = ray(point(1, 2, 3), vector(0, 1, 0));
}

void	fini_raytransform(void) {
	destroy_ray(&r);
}

Test(transform_ray, translating_ray, .init=init_raytranform, .fini=fini_raytransform) {
	t_matrix	*t = translate(3, 4, 5);
	t_ray		*result = transform(r, t);
	t_point		expected_value =  point(4, 6, 8);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result->origin[i], expected_value[i], EPISLON);
	}
	free(t);
	destroy_ray(&result);
}

Test(transform_ray, scaling_ray, .init=init_raytranform, .fini=fini_raytransform)
{
	t_matrix	*t = scale(2, 3, 4);
	t_ray		*result = transform(r, t);
	t_ray		*expected_value = ray(point(2, 6, 12), vector(0, 3, 0));
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result->origin[i], expected_value->origin[i], EPISLON);
		cr_assert_float_eq(result->direction[i], expected_value->direction[i], EPISLON);
	}
	free(t);
	destroy_ray(&result);
	destroy_ray(&expected_value);
}

void	init_final_intersect(void) {
	r = ray(point(0, 0, -5), vector(0, 0, 1));
	s = new_object(SPHERE);
	s->inversed_transform = inverse(s->transform);
	head = NULL;
}

void	fini_final_intersect(void) {
	destroy_ray(&r);
	destroy_intersect(&head);
	r = NULL;
	s = NULL;
	head = NULL;
}

Test(fina_intersect, intersecting_a_scaled_sphere_with_a_ray, .init=init_final_intersect,
		.fini=fini_final_intersect) {
	calc_linear_transformation(s, scale(2, 2, 2));
	free(s->inversed_transform);
	s->inversed_transform = inverse(s->transform);
	head = intersect(s, r);
	cr_assert_float_eq(head->t, 3., EPISLON);
	cr_assert_float_eq(head->next->t, 7., EPISLON);
}

Test(fina_intersect, intersecting_a_translated_sphere_with_a_ray, .init=init_final_intersect,
		.fini=fini_final_intersect) {
	calc_linear_transformation(s, translate(5, 0, 0));
	free(s->inversed_transform);
	s->inversed_transform = inverse(s->transform);
	head = intersect(s, r);
	cr_assert_null(head);
}
