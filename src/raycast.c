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
	r->origin = point(origin[0], origin[1], origin[2]);
	r->direction = vector(direction[0], direction[1], direction[2]);
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
