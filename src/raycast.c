/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:54:51 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/11 15:00:35 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "tuples_utils.h"
#include <stdlib.h>

void	destroy_ray(t_ray **r)
{
	free((*r)->origin);
	free((*r)->direction);
	free(*r);
}

t_ray	*ray(t_point origin, t_vector direction)
{
	t_ray	*r;

	r = malloc(sizeof(t_ray));
	if (!r)
		return (NULL);
	if (!origin || !direction)
	{
		r->origin = NULL;
		r->direction = NULL;
	}
	else
	{
		r->origin = point(origin[0], origin[1], origin[2]);
		r->direction = vector(direction[0], direction[1], direction[2]);
	}
	return (r);
}

t_point	position(t_ray const *r, const float t)
{
	t_vector	tmp;
	t_point		result;

	tmp = scalar_multiplication(r->direction, t);
	result = add_tuples(tmp, r->origin);
	free(tmp);
	return (result);
}

t_tuple	prod_matrix_tuple(t_matrix *m, t_tuple t)
{
	float	tmp[4];
	int		row;
	t_tuple	*mtx;

	row = -1;
	mtx = m->mtx;
	while (++row < 4)
	{
		tmp[row] = mtx[row][0] * t[0]
			+ mtx[row][1] * t[1]
			+ mtx[row][2] * t[2]
			+ mtx[row][3] * t[3];
	}
	return (tuple(tmp[0], tmp[1], tmp[2], tmp[3]));
}

t_ray	*transform(t_ray *r, t_matrix *t)
{
	t_ray	*new_ray;

	new_ray = ray(NULL, NULL);
	if (!new_ray)
		return (NULL);
	new_ray->origin = prod_matrix_tuple(t, r->origin);
	new_ray->direction = prod_matrix_tuple(t, r->direction);
	return (new_ray);
}
