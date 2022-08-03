#include <criterion/criterion.h>
#include <stdbool.h>
#include "../src/shadows/shadows.h"

#define EPISLON 0.00001

static struct s_parameters_lighting    p;
static t_color  result, expected;
static struct s_world                   *world;
static t_light                          *light;

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

static void fini_world(void)
{
	destroy_world(&world);
}

static void init_lighting(void) {
	p.material = material();
	p.position = point(0, 0, 0);
}

static void fini_lighting(void) {
  free(p.eyev);
  free(p.normalv);
  destroy_material(&p.material);
  destroy_light(&p.light);
  free(result);
  free(expected);
  expected = NULL;
  result = NULL;
  p.eyev = NULL;
  p.normalv = NULL;
  p.material = NULL;
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
	t_obj    *s1 = new_object(SPHERE);
	t_obj    *s2 = new_object(SPHERE);
	calc_linear_transformation(s2, translate(0, 0, 10));
	struct s_intersect *head = NULL;
	s1->inversed_transform = inverse(s1->transform);
	s2->inversed_transform = inverse(s2->transform);
	add_back(&head, new_intersect(0, s1));
	add_back(&head, new_intersect(0, s2));
	world = init_world(light, head);
	t_ray       *r = ray(point(0, 0, 5), vector(0, 0, 1));
	struct s_intersect *i = new_intersect(4, s2);
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
	t_obj	*s = new_object(SPHERE);
	calc_linear_transformation(s, translate(0, 0, 1));
	s->inversed_transform = inverse(s->transform);
	struct s_intersect	*i = new_intersect(5, s);
	struct	s_comps	*comp = prepare_computations(i, r);
	if (comp->over_point[2] < -EPISLON/2. && comp->point[2] > comp->over_point[2])
		cr_assert(true);
	else
		cr_assert(false);
}