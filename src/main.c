/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:24:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/23 18:18:53 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "tuples_utils.h"
#include "shadows.h"
#include "lights.h"
#include <stdio.h>
#include <stdlib.h>

static t_light	*light;
static struct s_world *world;

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
	intersections(head, intersection(0, s1));
	intersections(head, intersection(0, s2));
	world = init_world(light, head);
}

int	main(void)
{
	default_world();
    t_point p = point(20, -20, 20);
	if (in_shadowed(world, p))
	{
		printf("True\n");
	}
	destroy_intersections(&world->obj);
	destroy_light(&world->light_src);
	free(p);
	return (0);
}
