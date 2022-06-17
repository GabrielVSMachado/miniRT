/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:53:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/16 22:20:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "raycast.h"
#include "tuples_utils.h"
#include <math.h>
#include <stdlib.h>
#include "intersections.h"

void	intersect(t_sphere *s, t_ray *r, t_xs *head)
{
	int		count;
	float	b;
	float	c;
	float	discriminant;

	b = dot_product(r->direction, r->origin);
	c = dot_product(r->origin, r->origin) - s->r;
	discriminant = powf(b, 2) - c;
	if (discriminant < 0)
		return ;
	count = 2 * (discriminant > 0) + (discriminant == 0);
	head->count += count;
	discriminant = sqrtf(discriminant);
	intersections(head, intersection(-b - discriminant, s));
	if (count == 2)
		intersections(head, intersection(-b + discriminant, s));
}

static t_intersect	*last_instersection(t_intersect *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	intersections(t_xs *head, t_intersect *new)
{
	if (!head->fnode)
		head->fnode = new;
	else
		last_instersection(head->fnode)->next = new;
}

t_intersect	*hit(t_xs *head)
{
	t_intersect	*ht;
	t_intersect	*low_non_negative;

	ht = head->fnode;
	low_non_negative = ht;
	while (ht)
	{
		if (ht->t > 0
			&& (low_non_negative->t > ht->t || low_non_negative->t < 0))
			low_non_negative = ht;
		ht = ht->next;
	}
	if (low_non_negative->t < 0)
		return (NULL);
	return (low_non_negative);
}
