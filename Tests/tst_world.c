#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/intersections/intersections.h"
#include "../src/phong_reflection_model/lights.h"
#include "../src/world/world.h"
#include "utils.h"

static struct s_world	*world;
static t_light			*light;
# define EPISLON 0.00001

void	fini_world(void)
{
	destroy_world(&world);
}

Test(world, create_a_world_with_null_values, .fini=fini_world)
{
	world = init_world(NULL, NULL);
	cr_assert_null(world->light_src);
	cr_assert_null(world->intersections);
}

static void	default_world(void)
{
	light = point_light(color(1, 1, 1), point(-10, 10, -10));
	struct s_intersect		*head = NULL;
	t_obj	*s1 = new_object(SPHERE);
	t_obj	*s2 = new_object(SPHERE);
	s1->material->c[0] = 0.8;
	s1->material->c[1] = 1.0;
	s1->material->c[2] = 0.6;
	s1->material->diffuse = 0.7;
	s1->material->specular = 0.2;
	calc_linear_transformation(s2, scale(0.5, 0.5, 0.5));
	s1->inversed_transform = inverse(s1->transform);
	s2->inversed_transform = inverse(s2->transform);
	add_back(&head, new_intersect(0, s1));
	add_back(&head, new_intersect(0, s2));
	world = init_world(light, head);
}

Test(world, default_world, .init=default_world, .fini=fini_world) {
	cr_assert_not_null(world->intersections);
	cr_assert_not_null(world->intersections->next);
	cr_assert_not_null(world->light_src);
}

Test(world, intersect_world, .init=default_world, .fini=fini_world)
{
	t_ray	*r = ray(point(0, 0, -5), vector(0, 0, 1));
	struct s_intersect	*result = intersect_world(world, r);
	double	expected_values[] = {4, 4.5, 5.5, 6};
	struct s_intersect *tmp = result;
	for (int i = 0; i < 4; i++) {
		cr_assert_float_eq(tmp->t, expected_values[i], EPISLON);
		tmp = tmp->next;
	}
}

Test(prepare_computations, shading_an_intersection, .init=default_world, .fini=fini_world)
{
	t_ray *r = ray(point(0, 0, -5), vector(0, 0, 1));
	struct s_intersect	*intersec = new_intersect(4, world->intersections->obj);
	struct s_comps *comps = prepare_computations(intersec, r);
	t_color		c = shade_hit(world, comps);
	double		expected[] = {0.38066, 0.47583, 0.2855};
	for (int i = 0; i < 3; i++) {
		cr_assert_float_eq(c[i], expected[i], EPISLON);
	}
}

Test(prepare_computations, shading_an_intersection_from_inside, .init=default_world, .fini=fini_world)
{
	t_ray *r = ray(point(0, 0, 0), vector(0, 0, 1));
	world->light_src = point_light(color(1, 1, 1), point(0, 0.25, 0));
	struct s_intersect	*intersec = new_intersect(0.5, world->intersections->next->obj);
	struct s_comps	*comps = prepare_computations(intersec, r);
	t_color			result = shade_hit(world, comps);
	double			expected[] = {0.90498, 0.90498, 0.90498};
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
	world->intersections->obj->material->ambient = 1;
	world->intersections->next->obj->material->ambient = 1;
	t_color expected = world->intersections->next->obj->material->c;
	t_ray *r = ray(point(0, 0, 0.75), vector(0, 0, -1));
	t_color result = color_at(world, r);
	for (int i = 0; i < 3; ++i) {
		cr_assert_float_eq(result[i], expected[i], EPISLON);
	}
}
