/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:58:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/11 19:27:33 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "raycast.h"
#include "tuples_utils.h"
#include <math.h>
#include <stdlib.h>

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->center = 0;
	s->r = 1;
	return (s);
}

t_xs	*intersect(t_sphere *s, t_ray *r)
{
	t_xs	*xs;
	float	b;
	float	c;
	float	discriminant;

	b = dot_product(r->direction, r->origin);
	c = dot_product(r->origin, r->origin) - s->r;
	discriminant = powf(b, 2) - c;
	if (discriminant < 0)
		return (NULL);
	xs = malloc(sizeof(struct s_xs));
	if (!xs)
		return (NULL);
	xs->count = 2 * (discriminant > 0) + (discriminant == 0);
	discriminant = sqrtf(discriminant);
	xs->psec[0] = -b - discriminant;
	xs->psec[1] = -b + discriminant;
	return (xs);
}
