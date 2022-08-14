#include <criterion/criterion.h>
#include <stdio.h>
#include "../src/objects/object.h"
#include "../src/intersections/intersections.h"
#include <math.h>
#include <stdbool.h>

#define EPISLON 0.00001

Test(cylinder_intersect, a_ray_misses_a_cylinder_first)
{
	t_obj	*cylinder = new_cylinder();
	t_vector	direction = normalize(vector(0, 1, 0));
	t_ray	*r = ray(point(1, 0, 0), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_null(head);
}

Test(cylinder_intersect, a_ray_misses_a_cylinder_second)
{
	t_obj	*cylinder = new_cylinder();
	t_vector	direction = normalize(vector(0, 1, 0));
	t_ray	*r = ray(point(0, 0, 0), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_null(head);
}

Test(cylinder_intersect, a_ray_misses_a_cylinder_third)
{
	t_obj	*cylinder = new_cylinder();
	t_vector	direction = normalize(vector(1, 1, 1));
	t_ray	*r = ray(point(0, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_null(head);
}

Test(cylinder_intersect, a_ray_strike_a_cylinder_first)
{
	t_obj	*cylinder = new_cylinder();
	cylinder->inversed_transform = identity();
	t_vector direction = normalize(vector(0, 0, 1));
	t_ray	*r = ray(point(1, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_float_eq(head->t, 5., EPSILON);
}

Test(cylinder_intersect, a_ray_strike_a_cylinder_second)
{
	t_obj	*cylinder = new_cylinder();
	cylinder->inversed_transform = identity();
	t_vector direction = normalize(vector(0, 0, 1));
	t_ray	*r = ray(point(0, 0, -5), direction);
	struct s_intersect *head = cylinder_intersect(cylinder, r);
	cr_assert_float_eq(head->t, 4., EPSILON);
	cr_assert_float_eq(head->next->t, 6., EPSILON);
}

Test(cylinder_intersect, a_ray_strike_a_cylinder_third)
{
	t_obj	*cylinder = new_cylinder();
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
	t_obj	*obj = new_cylinder();
	t_vector	result = cylinder_normal_at(obj, point(1, 0, 0));
	cr_assert_float_eq(result[0], 1, EPISLON);
	cr_assert_float_eq(result[1], 0, EPISLON);
	cr_assert_float_eq(result[2], 0, EPISLON);
}

Test(cylinder_normal_at, normal_vector_on_a_cylinder_second)
{
	t_obj	*obj = new_cylinder();
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

Test(truncating, create_a_new_cylinder_with_default_values_eq_infinity)
{
	t_obj	*cylinder = new_cylinder();
	cr_assert(cylinder->attributes_cy.max == INFINITY);
	cr_assert(cylinder->attributes_cy.min == -INFINITY);
}

static struct s_intersect *test_truncating(t_vector direction, t_point origin)
{
	t_obj	*cylinder = new_cylinder();
	cylinder->attributes_cy.min = 1;
	cylinder->attributes_cy.max = 2;
	t_ray	*r = ray(origin, direction);
	struct s_intersect	*head = cylinder_intersect(cylinder, r);
	return head;
}

Test(truncating, intersecting_a_constrained_cylinder)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0.1, 1, 0)), point(0, 1.5, 0));
	cr_assert_null(head);
}

Test(truncating, intersecting_a_constrained_cylinder_second)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0, 0, 1)), point(0, 3, -5));
	cr_assert_null(head);
}

Test(truncating, intersecting_a_constrained_cylinder_third)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0, 0, 1)), point(0, 0, -5));
	cr_assert_null(head);
}

Test(truncating, intersecting_a_constrained_cylinder_fourth)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0, 0, 1)), point(0, 2, -5));
	cr_assert_null(head);
}

Test(truncating, intersecting_a_constrained_cylinder_fifth)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0, 0, 1)), point(0, 2, -5));
	cr_assert_null(head);
}

Test(truncating, intersecting_a_constrained_cylinder_sixth)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0, 0, 1)), point(0, 1, -5));
	cr_assert_null(head);
}

Test(truncating, intersecting_a_constrained_cylinder_seventh)
{
	struct s_intersect	*head = test_truncating(normalize(vector(0, 0, 1)), point(0, 1.5, -2));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

Test(is_closed, check_if_the_default_value_of_atributte_closed_is_false)
{
	t_obj	*cylinder = new_cylinder();
	cr_assert_eq(cylinder->attributes_cy.closed, false);
}

static struct s_intersect	*test_caps(t_vector direction, t_point	origin)
{
	t_obj	*cylinder = new_cylinder();
	cylinder->attributes_cy.max = 2;
	cylinder->attributes_cy.min = 1;
	cylinder->attributes_cy.closed = true;
	t_ray	*r = ray(origin, direction);
	struct s_intersect	*head = cylinder_intersect(cylinder, r);
	return head;
}

Test(is_closed, intersect_caps_of_a_closed_cylinder)
{
	struct s_intersect	*head = test_caps(normalize(vector(0, -1, 0)), point(0, 3, 0));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

Test(is_closed, intersect_caps_of_a_closed_cylinder_second)
{
	struct s_intersect	*head = test_caps(normalize(vector(0, -1, 2)), point(0, 3, -2));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

Test(is_closed, intersect_caps_of_a_closed_cylinder_third)
{
	struct s_intersect	*head = test_caps(normalize(vector(0, -1, 1)), point(0, 4, -2));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

Test(is_closed, intersect_caps_of_a_closed_cylinder_fourth)
{
	struct s_intersect	*head = test_caps(normalize(vector(0, 1, 2)), point(0, 0, -2));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

Test(is_closed, intersect_caps_of_a_closed_cylinder_fifth)
{
	struct s_intersect	*head = test_caps(normalize(vector(0, 1, 1)), point(0, -1, -2));
	cr_assert_not_null(head);
	cr_assert_not_null(head->next);
}

static t_vector	test_caps_normal(t_point origin)
{
	t_obj	*cylinder = new_cylinder();
	cylinder->attributes_cy.max = 2;
	cylinder->attributes_cy.min = 1;
	cylinder->attributes_cy.closed = true;
	return cylinder_normal_at(cylinder, origin);
}

Test(normal_at_with_caps, the_normal_vector_on_a_cylinder_end_caps)
{
	t_vector	normal = test_caps_normal(point(0, 1, 0));
	cr_assert_float_eq(normal[0], 0, EPISLON);
	cr_assert_float_eq(normal[1], -1, EPISLON);
	cr_assert_float_eq(normal[2], 0, EPISLON);
}

Test(normal_at_with_caps, the_normal_vector_on_a_cylinder_end_caps_second)
{
	t_vector	normal = test_caps_normal(point(0.5, 1, 0));
	cr_assert_float_eq(normal[0], 0, EPISLON);
	cr_assert_float_eq(normal[1], -1, EPISLON);
	cr_assert_float_eq(normal[2], 0, EPISLON);
}

Test(normal_at_with_caps, the_normal_vector_on_a_cylinder_end_caps_third)
{
	t_vector	normal = test_caps_normal(point(0, 1, 0.5));
	cr_assert_float_eq(normal[0], 0, EPISLON);
	cr_assert_float_eq(normal[1], -1, EPISLON);
	cr_assert_float_eq(normal[2], 0, EPISLON);
}

Test(normal_at_with_caps, the_normal_vector_on_a_cylinder_end_caps_fourth)
{
	t_vector	normal = test_caps_normal(point(0, 2, 0));
	cr_assert_float_eq(normal[0], 0, EPISLON);
	cr_assert_float_eq(normal[1], 1, EPISLON);
	cr_assert_float_eq(normal[2], 0, EPISLON);
}

Test(normal_at_with_caps, the_normal_vector_on_a_cylinder_end_caps_fifth)
{
	t_vector	normal = test_caps_normal(point(0.5, 2, 0));
	cr_assert_float_eq(normal[0], 0, EPISLON);
	cr_assert_float_eq(normal[1], 1, EPISLON);
	cr_assert_float_eq(normal[2], 0, EPISLON);
}

Test(normal_at_with_caps, the_normal_vector_on_a_cylinder_end_caps_sixth)
{
	t_vector	normal = test_caps_normal(point(0, 2, 0.5));
	cr_assert_float_eq(normal[0], 0, EPISLON);
	cr_assert_float_eq(normal[1], 1, EPISLON);
	cr_assert_float_eq(normal[2], 0, EPISLON);
}