/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:53:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/12 00:39:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "intersections.h"
#include "../ray/raycast.h"
#include "../world/world.h"

void	cpymatrices(t_matrix *dst, t_matrix *src)
{
	int	counter;

	counter = -1;
	while (++counter < (int)src->shape[0])
	{
		dst->mtx[counter][0] = src->mtx[counter][0];
		dst->mtx[counter][1] = src->mtx[counter][1];
		dst->mtx[counter][2] = src->mtx[counter][2];
		dst->mtx[counter][3] = src->mtx[counter][3];
	}
	dst->shape[0] = src->shape[0];
	dst->shape[1] = src->shape[1];
}

t_obj	*cpyobj(t_obj *src)
{
	t_obj	*cpy;

	cpy = new_object(src->type);
	cpy->material->ambient = src->material->ambient;
	cpy->material->diffuse = src->material->diffuse;
	cpy->material->shininess = src->material->shininess;
	cpy->material->specular = src->material->specular;
	cpy->material->c[0] = src->material->c[0];
	cpy->material->c[1] = src->material->c[1];
	cpy->material->c[2] = src->material->c[2];
	cpy->material->c[3] = src->material->c[3];
	cpymatrices(cpy->transform, src->transform);
	cpy->inversed_transform = malloc(sizeof(t_matrix));
	cpymatrices(cpy->inversed_transform, src->inversed_transform);
	cpy->local_intersect = src->local_intersect;
	cpy->local_normal_at = src->local_normal_at;
	return (cpy);
}

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
