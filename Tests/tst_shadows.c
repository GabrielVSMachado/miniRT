#include <criterion/criterion.h>
#include <stdbool.h>
#include "../src/lights.h"
#include "../src/intersections.h"
#include "../src/lights.h"
#include "../src/world.h"
#include "../src/shadows.h"
#include "../src/computations.h"

#define EPISLON 0.00001

static struct s_parameters_lighting    p;
static t_color  result, expected;
static struct s_world                   *world;
static t_light                          *light;


static void	default_world(void)
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
	s1->inverse_transform = inverse(s1->transform);
	s2->inverse_transform = inverse(s2->transform);
	intersections(head, intersection(0, s1));
	intersections(head, intersection(0, s2));
	world = init_world(light, head);
}

static void fini_world(void)
{
	destroy_light(&world->light_src);
	destroy_intersections(&world->obj);
}

static void init_lighting(void) {
	p.m = material();
	p.position = point(0, 0, 0);
}

static void fini_lighting(void) {
  free(p.eyev);
  free(p.normalv);
  destroy_material(&p.m);
  destroy_light(&p.light);
  free(result);
  free(expected);
  expected = NULL;
  result = NULL;
  p.eyev = NULL;
  p.normalv = NULL;
  p.m = NULL;
  p.light = NULL;
}

Test(shadow, lighting_with_a_surface_in_shadow, .init=init_lighting, .fini=fini_lighting)
{
	p.eyev = vector(0, 0, -1);
	p.normalv = vector(0, 0, -1);
	p.light = point_light(color(1, 1, 1), point(0, 0, -10));
	p.in_shadow = true;
	result = lighting(&p);
	expected = color(0.1, 0.1, 0.1);
	for (int i = 0; i < 3; i++)
	{
		cr_assert_float_eq(result[i], expected[i], EPISLON);
	}
}

Test(shadows, there_is_no_shadow_when_nothing_is_colinear_with_point_and_light, .init=default_world, .fini=fini_world)
{
	t_point p = point(0, 10, 0);
	cr_assert_eq(in_shadowed(world, p), false);
}

Test(shadows, the_shadow_when_an_object_is_between_the_point_and_the_light, .init=default_world, .fini=fini_world)
{
	t_point p = point(10, -10, 10);
	cr_assert_eq(in_shadowed(world, p), true);
}

Test(shadows, there_is_no_shadow_when_an_object_is_behind_the_light, .init=default_world, .fini=fini_world)
{
	t_point p = point(-20, 20, -20);
	cr_assert_eq(in_shadowed(world, p), false);
}

Test(shadows, there_is_no_shadow_when_an_object_is_behind_the_point, .init=default_world, .fini=fini_world)
{
	t_point p = point(-2, 2, -2);
	cr_assert_eq(in_shadowed(world, p), false);
}

Test(shade_hit, is_given_a_intersection_in_shadow)
{
	light = point_light(color(1, 1, 1), point(0, 0, -10));
	t_sphere    *s1 = sphere();
	t_sphere    *s2 = sphere();
	set_transform(s2, translate(0, 0, 10));
	t_xs        *head = init_xs();
	s1->inverse_transform = inverse(s1->transform);
	s2->inverse_transform = inverse(s2->transform);
	intersections(head, intersection(0, s1));
	intersections(head, intersection(0, s2));
	world = init_world(light, head);
	t_ray       *r = ray(point(0, 0, 5), vector(0, 0, 1));
	t_intersect *i = intersection(4, s2);
	struct  s_comps *comp = prepare_computations(i, r);
	t_color result = shade_hit(world, comp);
	for (int i = 0; i < 3; i++)
	{
		cr_assert_float_eq(result[i], 0.1, EPISLON);
	}
}

Test(check_new_attribute_over_point, the_hit_should_offset_the_point)
{
	t_ray	*r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	*s = sphere();
	set_transform(s, translate(0, 0, 1));
	t_intersect	*i = intersection(5, s);
	struct	s_comps	*comp = prepare_computations(i, r);
	if (comp->over_point[2] < -EPISLON/2. && comp->point[2] > comp->over_point[2])
		cr_assert(true);
	else
		cr_assert(false);
}