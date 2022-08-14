#include <criterion/criterion.h>
#include <stdio.h>
#include "../src/objects/object.h"
#include "../src/intersections/intersections.h"

#define EPISLON 0.00001

Test(cylinder_intersect, a_ray_misses_a_cylinder_first)
{
	t_obj	*cylinder = new_object(CYLINDER);
	t_vector	direction = normalize(vector(0, 1, 0));
	t_ray	*r = ray(point(1, 0, 0), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_null(head);
}

Test(cylinder_intersect, a_ray_misses_a_cylinder_second)
{
	t_obj	*cylinder = new_object(CYLINDER);
	t_vector	direction = normalize(vector(0, 1, 0));
	t_ray	*r = ray(point(0, 0, 0), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_null(head);
}

Test(cylinder_intersect, a_ray_misses_a_cylinder_third)
{
	t_obj	*cylinder = new_object(CYLINDER);
	t_vector	direction = normalize(vector(1, 1, 1));
	t_ray	*r = ray(point(0, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_null(head);
}

	Test(cylinder_intersect, a_ray_strike_a_cylinder_first)
{
	t_obj	*cylinder = new_object(CYLINDER);
	cylinder->inversed_transform = identity();
	t_vector direction = normalize(vector(0, 0, 1));
	t_ray	*r = ray(point(1, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_float_eq(head->t, 5., EPSILON);
}

Test(cylinder_intersect, a_ray_strike_a_cylinder_second)
{
	t_obj	*cylinder = new_object(CYLINDER);
	cylinder->inversed_transform = identity();
	t_vector direction = normalize(vector(0, 0, 1));
	t_ray	*r = ray(point(0, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_float_eq(head->t, 4., EPSILON);
	cr_assert_float_eq(head->next->t, 6., EPSILON);
}

Test(cylinder_intersect, a_ray_strike_a_cylinder_third)
{
	t_obj	*cylinder = new_object(CYLINDER);
	cylinder->inversed_transform = identity();
	t_vector direction = normalize(vector(0.1, 1, 1));
	direction[3] = 0;
	t_ray	*r = ray(point(0.5, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_float_eq(head->t, 6.80798, EPISLON);
	cr_assert_float_eq(head->next->t, 7.08872, EPISLON);
}

Test(cylinder_normal_at, normal_vector_on_a_cylinder)
{
	t_obj	*obj = new_object(CYLINDER);
	t_vector	result = cylinder_normal_at(obj, point(1, 0, 0));
	cr_assert_float_eq(result[0], 1, EPISLON);
	cr_assert_float_eq(result[1], 0, EPISLON);
	cr_assert_float_eq(result[2], 0, EPISLON);
}

Test(cylinder_normal_at, normal_vector_on_a_cylinder_second)
{
	t_obj	*obj = new_object(CYLINDER);
	t_vector	result = cylinder_normal_at(obj, point(0, 5, -1));
	cr_assert_float_eq(result[0], 0, EPISLON);
	cr_assert_float_eq(result[1], 0, EPISLON);
	cr_assert_float_eq(result[2], -1, EPISLON);
}

Test(cylinder_normal_at, normal_vector_on_a_cylinder_third)
{
	t_obj	*obj = new_object(CYLINDER);
	t_vector	result = cylinder_normal_at(obj, point(0, -2, 1));
	cr_assert_float_eq(result[0], 0, EPISLON);
	cr_assert_float_eq(result[1], 0, EPISLON);
	cr_assert_float_eq(result[2], 1, EPISLON);
}

Test(cylinder_normal_at, normal_vector_on_a_cylinder_fourty)
{
	t_obj	*obj = new_object(CYLINDER);
	t_vector	result = cylinder_normal_at(obj, point(-1, -1, 0));
	cr_assert_float_eq(result[0], -1, EPISLON);
	cr_assert_float_eq(result[1], 0, EPISLON);
	cr_assert_float_eq(result[2], 0, EPISLON);
}