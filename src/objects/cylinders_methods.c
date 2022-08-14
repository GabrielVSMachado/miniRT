/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:51:33 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/13 22:33:54 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>
#include <math.h>
#include "../world/world.h"

struct s_intersect	*cylinder_intersect(t_obj *cylinder, t_ray *r)
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
	struct s_intersect	*head;

	head = NULL;
	a = pow(r->direction[0], 2) + pow(r->direction[2], 2);
	if ((int)(a * pow(10, 4)) == 0)
		return (NULL);
	b = 2 * r->direction[0] * r->origin[0] + 2 * r->direction[2] * r->origin[2];
	c = pow(r->origin[0], 2) + pow(r->origin[2], 2) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return (NULL);
	discriminant = sqrt(discriminant);
	add_back(&head, new_intersect((-b - discriminant) / (2 * a), cylinder));
	if (discriminant)
		add_back(&head, new_intersect(
				(-b + discriminant) / (2 * a), cylinder));
	return (head);
}

t_vector	cylinder_normal_at(t_obj *cylinder, t_point p)
{
	cylinder = (t_obj *)cylinder;
	return (vector(p[0], 0, p[2]));
}
