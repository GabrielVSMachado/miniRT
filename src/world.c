/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:07:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/25 19:24:38 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadows.h"
#include "world.h"
#include "computations.h"
#include "intersections.h"
#include "lights.h"
#include "miniRT.h"
#include "raycast.h"
#include "sphere.h"
#include "tuples_utils.h"
#include "utils_colors.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

struct s_world	*init_world(t_light *light, t_xs *head)
{
	struct s_world	*new_world;

	new_world = malloc(sizeof(struct s_world));
	if (!new_world)
		return (NULL);
	new_world->light_src = light;
	new_world->obj = head;
	return (new_world);
}

t_xs	*intersect_world(struct s_world *w, t_ray *r)
{
	t_xs		*head;
	t_intersect	*tmp;

	head = init_xs();
	if (!head)
		return (NULL);
	tmp = w->obj->fnode;
	while (tmp)
	{
		intersect(tmp->obj, r, head);
		tmp = tmp->next;
	}
	bubblesort(head);
	return (head);
}

t_color	shade_hit(struct s_world *w, struct s_comps *comps)
{
	return (
		lighting(&(struct s_parameters_lighting){
			.m = comps->obj->m,
			.light = w->light_src,
			.position = comps->point,
			.eyev = comps->eyev,
			.normalv = comps->normalv,
			.in_shadow = in_shadowed(w, comps->over_point)})
			);
}

t_color	color_at(struct s_world *w, t_ray *r)
{
	t_xs			*head;
	t_intersect		*hitnode;
	struct s_comps	*comps;
	t_color			c;

	head = intersect_world(w, r);
	hitnode = hit(head);
	if (hitnode)
	{
		comps = prepare_computations(hitnode, r);
		c = shade_hit(w, comps);
		destroy_intersections(&head);
		destroy_comps(&comps);
		return (c);
	}
	destroy_intersections(&head);
	return (color(0, 0, 0));
}
