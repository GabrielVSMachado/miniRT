#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/world.h"

static struct s_world	*world;
static t_light			*light;
# define EPISLON 0.00001

void	fini_world(void)
{
	destroy_intersections(&world->obj);
	destroy_light(&world->light_src);
	free(world);
	world = NULL;
}

Test(world, create_a_world_with_null_values, .fini=fini_world)
{
	world = init_world(NULL, NULL);
	cr_assert_null(world->light_src);
	cr_assert_null(world->obj);
}

void	default_world(void)
{
	light = point_light(color(1, 1, 1), point(-10, 10, -10));
	t_xs		*head = init_xs();
	t_sphere	*s1 = sphere();
	t_sphere	*s2 = sphere();
	s1->m->c[0] = 0.8;
	s1->m->c[1] = 1.0;
	s1->m->c[2] = 0.6;
	s1->m->diffuse = 0.7;
	s1->m->specular = 0.2;
	set_transform(s2, scale(0.5, 0.5, 0.5));
	intersections(head, intersection(0, s1));
	intersections(head, intersection(0, s2));
	world = init_world(light, head);
}

Test(world, default_world, .init=default_world, .fini=fini_world) {
	cr_assert_not_null(world->obj->fnode);
	cr_assert_not_null(world->obj->fnode->next);
	cr_assert_not_null(world->light_src);
}

Test(world, intersect_world, .init=default_world, .fini=fini_world)
{
	t_ray	*r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_xs	*result = intersect_world(world, r);
	float	expected_values[] = {4, 4.5, 5.5, 6};
	t_intersect *tmp = result->fnode;
	cr_assert_eq(result->count, 4);
	for (int i = 0; i < 4; i++) {
		cr_assert_float_eq(tmp->t, expected_values[i], EPISLON);
		tmp = tmp->next;
	}
}

Test(prepare_computations, shading_an_intersection, .init=default_world, .fini=fini_world)
{
	t_ray *r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_intersect	*intersec = intersection(4, world->obj->fnode->obj);
	struct s_comps *comps = prepare_computations(intersec, r);
	t_color		c = shade_hit(world, comps);
	float		expected[] = {0.38066, 0.47583, 0.2855};
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(c[i], expected[i], EPISLON);
	}
}

Test(prepare_computations, shading_an_intersection_from_inside, .init=default_world, .fini=fini_world)
{
	t_ray *r = ray(point(0, 0, 0), vector(0, 0, 1));
	world->light_src = point_light(color(1, 1, 1), point(0, 0.25, 0));
	t_intersect	*intersec = intersection(0.5, world->obj->fnode->next->obj);
	struct s_comps	*comps = prepare_computations(intersec, r);
	t_color			result = shade_hit(world, comps);
	float			expected[] = {0.90498, 0.90498, 0.90498};
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], expected[i], EPISLON);
	}
}

Test(color_at, the_color_when_a_ray_misses, .init=default_world, .fini=fini_world)
{
	t_ray *r = ray(point(0, 0, -5), vector(0, 1, 0));
	t_color	result = color_at(world, r);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], 0, EPISLON);
	}
}

Test(color_at, the_color_when_a_ray_hit, .init=default_world, .fini=fini_world)
{
	t_ray	*r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_color	result = color_at(world, r);
	t_color expected = color(0.38066, 0.47583, 0.2855);
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(result[i], expected[i], EPISLON);
	}
}

Test(color_at, the_color_with_an_intersection_behind_the_ray, .init=default_world, .fini=fini_world)
{
	world->obj->fnode->obj->m->ambient = 1;
	world->obj->fnode->next->obj->m->ambient = 1;
	t_color expected = world->obj->fnode->next->obj->m->c;
	t_ray *r = ray(point(0, 0, 0.75), vector(0, 0, -1));
	t_color result = color_at(world, r);
	for (int i = 0; i < 3; ++i) {
		cr_assert_float_eq(result[i], expected[i], EPISLON);
	}
}
