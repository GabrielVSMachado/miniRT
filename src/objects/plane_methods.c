/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:16:34 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/09 23:27:18 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "../world/world.h"
#include <stdlib.h>
#include <math.h>

t_vector	plane_normal_at(t_obj *plane, t_point	point)
{
	plane = (t_obj *)plane;
	point = (t_point)point;
	return (vector(0, 1, 0));
}

struct s_intersect	*plane_intersect(t_obj *plane, t_ray *r)
{
	double	t;

	if (fabs(r->direction[1]) < EPSILON)
		return (NULL);
	t = -r->origin[1] / r->direction[1];
	return (new_intersect(t, plane));
}
