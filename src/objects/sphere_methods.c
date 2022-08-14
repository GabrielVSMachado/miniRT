/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:42:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/13 22:34:00 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>
#include <math.h>
#include "../intersections/intersections.h"

static double	calc_discriminant(double *a, double *b, t_ray *r)
{
	double	c;

	*a = dot_product(r->direction, r->direction);
	*b = 2 * dot_product(r->direction, r->origin);
	c = dot_product(r->origin, r->origin) - 1;
	return (pow(*b, 2) - 4 * (*a) * c);
}

struct s_intersect	*sphere_intersect(t_obj *obj, t_ray *r)
{
	double				discriminant;
	double				a;
	double				b;
	struct s_intersect	*head;

	head = NULL;
	discriminant = calc_discriminant(&a, &b, r);
	if (discriminant < 0)
		return (NULL);
	discriminant = sqrt(discriminant);
	add_back(&head, new_intersect((-b - discriminant) / (2 * a), obj));
	if (discriminant)
		add_back(&head, new_intersect(
				(-b + discriminant) / (2 * a), obj));
	return (head);
}

t_vector	sphere_normal_at(t_obj *sphere, t_point world_point)
{
	t_tuple	normal;
	t_tuple	sub;
	t_point	origin;

	sphere = (t_obj *)sphere;
	origin = point(0, 0, 0);
	sub = sub_tuple(world_point, origin);
	normal = normalize(world_point);
	free(sub);
	free(origin);
	return (normal);
}
