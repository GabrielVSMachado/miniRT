/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:53:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/08 22:22:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>

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

t_vector	normal_at(t_obj *obj, t_point world_point)
{
	t_vector	obj_normal;
	t_vector	world_normal;
	t_matrix	*transposed_im;
	t_vector	normal;

	obj_normal = prod_matrix_tuple(obj->inversed_transform, world_point);
	obj_normal[3] = 0;
	transposed_im = tranposing(obj->inversed_transform);
	world_normal = prod_matrix_tuple(transposed_im, obj_normal);
	world_normal[3] = 0;
	normal = normalize(world_normal);
	free(transposed_im);
	free(world_normal);
	free(obj_normal);
	return (normal);
}
