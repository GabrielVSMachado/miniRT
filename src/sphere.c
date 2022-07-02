/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:58:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/16 13:55:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include <stdlib.h>
#include "matrix.h"
#include "raycast.h"
#include "tuples_utils.h"

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->transform = identity();
	return (s);
}

void	destroy_sphere(t_sphere **s)
{
	destroy_matrix(&(*s)->transform);
	free(*s);
	*s = NULL;
}

void	set_transform(t_sphere *s, t_matrix *t)
{
	t_matrix	*product;

	product = matrices_product(t, s->transform);
	destroy_matrix(&s->transform);
	s->transform = product;
}

t_vector	normal_at(t_sphere *s, t_point world_point)
{
	t_vector	obj_normal;
	t_vector	world_normal;
	t_matrix	*tmp;
	t_matrix	*mt;
	t_vector	normal;

	mt = inverse(s->transform);
	obj_normal = prod_matrix_tuple(mt, world_point);
	obj_normal[3] = 0;
	tmp = tranposing(mt);
	destroy_matrix(&mt);
	mt = tmp;
	world_normal = prod_matrix_tuple(mt, obj_normal);
	world_normal[3] = 0;
	normal = normalize(world_normal);
	free(world_normal);
	return (normal);
}
