#include <criterion/criterion.h>
#include "../src/objects/object.h"
#include "../src/intersections/intersections.h"
#include "utils.h"

#define EPISLON 0.00001

Test(plane_normal_at, expected_the_same_vector_0_1_0)
{
	t_obj	*p = new_object(PLANE);
	t_vector	results[] = {
		plane_normal_at(p, point(0, 0, 0)),
		plane_normal_at(p, point(10, 0, -10)),
		plane_normal_at(p, point(-5, 0, 150))
	};
	for (int i = 0; i < 3; i++)
	{
		cr_assert_float_eq(results[i][0], 0, EPISLON);
		cr_assert_float_eq(results[i][1], 1., EPISLON);
		cr_assert_float_eq(results[i][2], 0, EPISLON);
	}
	free(results[0]);
	free(results[1]);
	free(results[2]);
}

Test(plane_intersect, intersect_with_a_ray_parallel_to_the_plane)
{
	t_obj	*p	= new_object(PLANE);
	t_ray	*r = ray(point(0, 10, 0), vector(0, 0, 1));
	struct s_intersect	*head = p->_intersect(p, r);
	cr_assert_null(head);
	destroy_object(&p);
	destroy_ray(&r);
}

Test(plane_intersect, intersect_with_a_coplanar_ray)
{
	t_obj	*p	= new_object(PLANE);
	t_ray	*r = ray(point(0, 0, 0), vector(0, 0, 1));
	struct s_intersect	*head = p->_intersect(p, r);
	cr_assert_null(head);
	destroy_object(&p);
	destroy_ray(&r);
}

Test(plane_intersect, a_ray_intersect_the_plane_from_above)
{
	t_obj	*p = new_object(PLANE);
	t_ray	*r = ray(point(0, 1, 0), vector(0, -1, 0));
	struct s_intersect	*head = p->_intersect(p, r);
	cr_assert_float_eq(head->t, 1., EPISLON);
	cr_assert_eq(head->obj->type, PLANE);
	assert_matrices(p->transform->mtx, head->obj->transform->mtx, p->transform->shape);
	cr_assert_float_eq(p->material->ambient, head->obj->material->ambient, EPISLON);
	cr_assert_float_eq(p->material->diffuse, head->obj->material->diffuse, EPISLON);
	cr_assert_float_eq(p->material->specular, head->obj->material->specular, EPISLON);
	cr_assert_float_eq(p->material->shininess, head->obj->material->shininess, EPISLON);
	cr_assert_float_eq(p->material->c[0], head->obj->material->c[0], EPISLON);
	cr_assert_float_eq(p->material->c[1], head->obj->material->c[1], EPISLON);
	cr_assert_float_eq(p->material->c[2], head->obj->material->c[2], EPISLON);
}

Test(plane_intersect, a_ray_intersect_the_plane_from_below)
{
	t_obj	*p = new_object(PLANE);
	t_ray	*r = ray(point(0, -1, 0), vector(0, 1, 0));
	struct s_intersect	*head = p->_intersect(p, r);
	cr_assert_float_eq(head->t, 1., EPISLON);
	cr_assert_eq(head->obj->type, PLANE);
	assert_matrices(p->transform->mtx, head->obj->transform->mtx, p->transform->shape);
	cr_assert_float_eq(p->material->ambient, head->obj->material->ambient, EPISLON);
	cr_assert_float_eq(p->material->diffuse, head->obj->material->diffuse, EPISLON);
	cr_assert_float_eq(p->material->specular, head->obj->material->specular, EPISLON);
	cr_assert_float_eq(p->material->shininess, head->obj->material->shininess, EPISLON);
	cr_assert_float_eq(p->material->c[0], head->obj->material->c[0], EPISLON);
	cr_assert_float_eq(p->material->c[1], head->obj->material->c[1], EPISLON);
	cr_assert_float_eq(p->material->c[2], head->obj->material->c[2], EPISLON);
}