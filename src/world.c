/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:07:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/09 13:04:53 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "intersections.h"
#include "lights.h"
#include "miniRT.h"
#include "raycast.h"
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
