/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders_methods_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:12:54 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/14 16:56:34 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <math.h>
#include <stdlib.h>
#include "../intersections/intersections.h"

static bool	check_caps(t_ray *r, double t)
{
	double	x;
	double	z;

	x = r->origin[0] + t * r->direction[0];
	z = r->origin[2] + t * r->direction[2];
	return ((pow(x, 2) + pow(z, 2)) <= 1);
}

struct s_intersect	*intersect_caps(t_obj *cylinder, t_ray *r)
{
	struct s_intersect	*head;
	double				t;

	head = NULL;
	t = (cylinder->attributes_cy.min - r->origin[1]) / r->direction[1];
	if (check_caps(r, t))
		add_back(&head, new_intersect(t, cylinder));
	t = (cylinder->attributes_cy.max - r->origin[1]) / r->direction[1];
	if (check_caps(r, t))
		add_back(&head, new_intersect(t, cylinder));
	return (head);
}
