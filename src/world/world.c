/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:07:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/02 22:54:21 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../phong_reflection_model/lights.h"
#include "../ray/raycast.h"
#include "../intersections/intersections.h"
#include "world.h"

struct s_world	*init_world(t_light *light, struct s_intersect *head)
{
	struct s_world	*new_world;

	new_world = malloc(sizeof(struct s_world));
	if (!new_world)
		return (NULL);
	new_world->light_src = light;
	new_world->intersections = head;
	return (new_world);
}

t_color	shade_hit(struct s_world *w, struct s_comps *comps)
{
	return (
		lighting(&(struct s_parameters_lighting){
			.material = comps->obj->material,
			.light = w->light_src,
			.position = comps->point,
			.eyev = comps->eyev,
			.normalv = comps->normalv,
			.in_shadow = false})
			);
}

t_color	color_at(struct s_world *w, t_ray *r)
{
	struct s_intersect	*head;
	struct s_intersect	*hitnode;
	struct s_comps		*comps;
	t_color				c;

	head = intersect_world(w, r);
	hitnode = hit(head);
	if (hitnode)
	{
		comps = prepare_computations(hitnode, r);
		c = shade_hit(w, comps);
		destroy_intersect(&head);
		destroy_comps(&comps);
		return (c);
	}
	destroy_intersect(&head);
	return (color(0, 0, 0));
}

struct s_intersect	*intersect_world(struct s_world *world, t_ray *r)
{
	struct s_intersect	*head;
	struct s_intersect	*tmp;

	head = NULL;
	tmp = world->intersections;
	while (tmp)
	{
		add_back(&head, intersect(tmp->obj, r));
		tmp = tmp->next;
	}
	bubblesort(head);
	return (head);
}

void	destroy_world(struct s_world **world)
{
	destroy_intersect(&(*world)->intersections);
	destroy_light(&(*world)->light_src);
	free(*world);
	*world = NULL;
}
