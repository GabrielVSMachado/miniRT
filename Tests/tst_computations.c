#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "../src/world/world.h"
#include "utils.h"

#define EPISLON 0.00001

Test(prepare_computations, precomputing_the_state_of_an_intersection)
{
	t_obj	*obj = new_object(SPHERE);
	obj->inversed_transform = inverse(obj->transform);
	struct s_intersect *i = new_intersect(4, obj);
	t_ray		*r = ray(point(0, 0, -5), vector(0, 0, 1));
	struct s_comps *result = prepare_computations(i, r);
	cr_assert_float_eq(result->t, i->t, EPISLON);
	cr_assert(assert_matrices(result->obj->transform->mtx, i->obj->transform->mtx, i->obj->transform->shape) == true);
	cr_assert_float_eq(result->obj->material->ambient, i->obj->material->ambient, EPISLON);
	cr_assert_float_eq(result->obj->material->diffuse, i->obj->material->diffuse, EPISLON);
	cr_assert_float_eq(result->obj->material->shininess, i->obj->material->shininess, EPISLON);
	cr_assert_float_eq(result->obj->material->specular, i->obj->material->specular, EPISLON);
	for (int j = 0; j < 3; j++) {
		cr_assert_float_eq(result->obj->material->c[j], i->obj->material->c[j], EPISLON);
	}
	double	expected[] = {0, 0, -1};
	for (int i = 0; i < 3; i++)
	{
		cr_assert_float_eq(result->eyev[i], expected[i], EPISLON);
		cr_assert_float_eq(result->normalv[i], expected[i], EPISLON);
		cr_assert_float_eq(result->point[i], expected[i], EPISLON);
	}
}

Test(prepare_computations, the_hit_when_an_intersection_occurs_on_the_outside)
{
	t_obj	*obj = new_object(SPHERE);
	obj->inversed_transform = inverse(obj->transform);
	t_ray		*r = ray(point(0, 0, -5), vector(0, 0, 1));
	struct s_intersect	*intersec = new_intersect(4, obj);
	struct s_comps *comp = prepare_computations(intersec, r);
	cr_assert_eq(comp->inside, false);
}

Test(prepare_computations, the_hit_when_an_intersection_occurs_on_the_inside)
{
	t_obj	*obj = new_object(SPHERE);
	obj->inversed_transform = inverse(obj->transform);
	t_ray	*r = ray(point(0, 0, 0), vector(0, 0, 1));
	struct s_intersect	*intersec = new_intersect(4, obj);
	struct s_comps	*comp = prepare_computations(intersec, r);
	cr_assert_eq(comp->inside, true);
}
