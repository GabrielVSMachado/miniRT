/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:54:51 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/29 19:37:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <stdlib.h>
#include "../vectors/vectors.h"

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
	r->origin = origin;
	r->direction = direction;
	return (r);
}

t_point	position(t_ray const *r, const double t)
{
	t_vector	tmp;
	t_point		result;

	tmp = scalar_multiplication(r->direction, t);
	result = add_tuples(tmp, r->origin);
	free(tmp);
	return (result);
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
