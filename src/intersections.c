/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:53:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/11 19:52:39 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "raycast.h"
#include "tuples_utils.h"
#include <math.h>
#include <stdlib.h>
#include "intersections.h"

static float	calc_discriminant(float constants[], t_ray *r)
{
	float	a;
	float	b;
	float	c;

	a = dot_product(r->direction, r->direction);
	b = 2 * dot_product(r->direction, r->origin);
	c = dot_product(r->origin, r->origin) - 1;
	constants[0] = a;
	constants[1] = b;
	return (powf(b, 2) - 4 * a * c);
}

void	intersect(t_sphere *s, t_ray *r, t_xs *head)
{
	float		discriminant;
	float		constants[2];
	t_ray		*tmp;
	t_matrix	*inv_sph_transform;

	inv_sph_transform = inverse(s->transform);
	tmp = transform(r, inv_sph_transform);
	discriminant = calc_discriminant(constants, tmp);
	destroy_matrix(&inv_sph_transform);
	destroy_ray(&tmp);
	if (discriminant < 0)
		return ;
	discriminant = sqrtf(discriminant);
	head->count += 2 * (discriminant > 0) + (discriminant == 0);
	intersections(head, intersection(
			(-constants[1] - discriminant) / (2 * constants[0]), s));
	if (discriminant)
		intersections(head, intersection(
				(-constants[1] + discriminant) / (2 * constants[0]), s));
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

	if (!head->fnode)
		return (NULL);
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
