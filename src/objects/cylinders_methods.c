/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:51:33 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/17 23:16:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>
#include <math.h>
#include "../world/world.h"

static void	swap(double *t0, double *t1)
{
	double	tmp;

	tmp = *t0;
	*t0 = *t1;
	*t1 = tmp;
}

static struct s_intersect	*add_intersections(
	t_obj *cylinder, t_ray *r, double t0, double t1)
{
	struct s_intersect	*head;
	double				y0;
	double				y1;

	if (t0 > t1)
		swap(&t0, &t1);
	head = NULL;
	y0 = r->origin[1] + t0 * r->direction[1];
	if (cylinder->attributes_cy.max > y0 && cylinder->attributes_cy.min < y0)
		add_back(&head, new_intersect(t0, cylinder));
	y1 = r->origin[1] + t1 * r->direction[1];
	if (cylinder->attributes_cy.max > y1 && cylinder->attributes_cy.min < y1)
		add_back(&head, new_intersect(t1, cylinder));
	return (head);
}

struct s_intersect	*cylinder_intersect(t_obj *cylinder, t_ray *r)
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
	struct s_intersect	*head;

	head = NULL;
	a = pow(r->direction[0], 2) + pow(r->direction[2], 2);
	if ((int)(a * pow(10, 4)) != 0)
	{
		b = 2 * r->direction[0] * r->origin[0]
			+ 2 * r->direction[2] * r->origin[2];
		c = pow(r->origin[0], 2) + pow(r->origin[2], 2) - 1;
		discriminant = pow(b, 2) - 4. * a * c;
		if (discriminant < 0)
			return (NULL);
		discriminant = sqrt(discriminant);
		head = add_intersections(
				cylinder, r, (-b - discriminant) / (2. * a),
				(-b + discriminant) / (2. * a)
				);
	}
	if (cylinder->attributes_cy.closed)
		add_back(&head, intersect_caps(cylinder, r));
	return (head);
}

t_vector	cylinder_normal_at(t_obj *cylinder, t_point p)
{
	double	dist;

	dist = pow(p[0], 2) + pow(p[2], 2);
	if (dist < 1)
	{
		if (p[1] >= cylinder->attributes_cy.max - EPSILON)
			return (vector(0, 1, 0));
		else if (p[1] <= cylinder->attributes_cy.min + EPSILON)
			return (vector(0, -1, 0));
	}
	return (vector(p[0], 0, p[2]));
}

t_obj	*new_cylinder(void)
{
	t_obj	*new;

	new = new_object(CYLINDER, material(color(1, 1, 1), color(0.5, 1, 1), 0.1));
	if (!new)
		return (NULL);
	new->attributes_cy.max = INFINITY;
	new->attributes_cy.min = -INFINITY;
	new->attributes_cy.closed = false;
	return (new);
}
