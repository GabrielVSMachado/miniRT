/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:53:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/13 21:07:50 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>
#include "../intersections/intersections.h"

t_obj	*new_object(unsigned int type)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	if (!new)
		return (NULL);
	new->type = type;
	new->transform = identity();
	new->inversed_transform = NULL;
	new->material = material();
	if (type == PLANE)
	{
		new->local_normal_at = plane_normal_at;
		new->local_intersect = plane_intersect;
	}
	else if (type == SPHERE)
	{
		new->local_intersect = sphere_intersect;
		new->local_normal_at = sphere_normal_at;
	}
	else
	{
		new->local_intersect = cylinder_intersect;
		new->local_normal_at = cylinder_normal_at;
	}
	return (new);
}

void	destroy_object(t_obj **obj)
{
	free((*obj)->inversed_transform);
	free((*obj)->transform);
	destroy_material(&(*obj)->material);
	free(*obj);
	*obj = NULL;
}

void	calc_linear_transformation(t_obj *obj, t_matrix *transform)
{
	t_matrix	*new_linear_transform;

	new_linear_transform = matrices_product(transform, obj->transform);
	free(obj->transform);
	free(transform);
	obj->transform = new_linear_transform;
}
