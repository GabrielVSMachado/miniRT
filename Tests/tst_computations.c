#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "../src/world.h"

#define EPISLON 0.00001

Test(prepare_computations, precomputing_the_state_of_an_intersection)
{
	t_intersect *i = intersection(4, sphere());
	t_ray		*r = ray(point(0, 0, -5), vector(0, 0, 1));
	struct s_comps *result = prepare_computations(i, r);
	cr_assert_float_eq(result->t, i->t, EPISLON);
	cr_assert(assert_t_matrix_eq(result->obj->transform, i->obj->transform) == true);
	cr_assert_float_eq(result->obj->m->ambient, i->obj->m->ambient, EPISLON);
	cr_assert_float_eq(result->obj->m->diffuse, i->obj->m->diffuse, EPISLON);
	cr_assert_float_eq(result->obj->m->shininess, i->obj->m->shininess, EPISLON);
	cr_assert_float_eq(result->obj->m->specular, i->obj->m->specular, EPISLON);
	for (int j = 0; j < 3; j++) {
		cr_assert_float_eq(result->obj->m->c[j], i->obj->m->c[j], EPISLON);
	}
	float	expected[] = {0, 0, -1};
	for (int i = 0; i < 3; i++)
	{
		cr_assert_float_eq(result->eyev[i], expected[i], EPISLON);
		cr_assert_float_eq(result->normalv[i], expected[i], EPISLON);
		cr_assert_float_eq(result->point[i], expected[i], EPISLON);
	}
}

Test(prepare_computations, the_hit_when_an_intersection_occurs_on_the_outside)
{
	t_ray		*r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersect	*intersec = intersection(4, sphere());
	struct s_comps *comp = prepare_computations(intersec, r);
	cr_assert_eq(comp->inside, false);
}

Test(prepare_computations, the_hit_when_an_intersection_occurs_on_the_inside)
{
	t_ray	*r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_intersect	*intersec = intersection(4, sphere());
	struct s_comps	*comp = prepare_computations(intersec, r);
	cr_assert_eq(comp->inside, true);
}
