/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:53:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/13 22:31:22 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "intersections.h"
#include "../ray/raycast.h"
#include "../world/world.h"

struct s_intersect	*intersect(t_obj *obj, t_ray *r)
{
	t_ray				*transformed_ray;
	struct s_intersect	*head;

	if (!obj->inversed_transform)
		return (NULL);
	transformed_ray = transform(r, obj->inversed_transform);
	head = obj->local_intersect(obj, transformed_ray);
	destroy_ray(&transformed_ray);
	return (head);
}

struct s_intersect	*hit(struct s_intersect *head)
{
	struct s_intersect	*lower_non_negative;

	if (!head)
		return (NULL);
	lower_non_negative = head;
	while (head)
	{
		if (head->t > 0
			&& (lower_non_negative->t > head->t || lower_non_negative->t < 0))
			lower_non_negative = head;
		head = head->next;
	}
	if (lower_non_negative->t < 0)
		return (NULL);
	return (lower_non_negative);
}

t_vector	normal_at(t_obj *obj, t_point p)
{
	t_point		local_point;
	t_vector	local_normal;
	t_matrix	*transposed_inverse;
	t_vector	world_normal;
	t_tuple		tmp;

	local_point = prod_matrix_tuple(obj->inversed_transform, p);
	local_normal = obj->local_normal_at(obj, local_point);
	transposed_inverse = tranposing(obj->inversed_transform);
	tmp = prod_matrix_tuple(transposed_inverse, local_normal);
	world_normal = normalize(tmp);
	free(local_point);
	free(local_normal);
	free(transposed_inverse);
	free(tmp);
	world_normal[3] = 0;
	return (world_normal);
}
