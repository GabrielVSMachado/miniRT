/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:53:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 18:20:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "../ray/raycast.h"
#include "intersections.h"

static double	calc_discriminant(double *a, double *b, t_ray *r)
{
	double	c;

	*a = dot_product(r->direction, r->direction);
	*b = 2 * dot_product(r->direction, r->origin);
	c = dot_product(r->origin, r->origin) - 1;
	return (powf(*b, 2) - 4 * (*a) * c);
}

struct s_intersect	*intersect(t_obj *obj, t_ray *r)
{
	double				discriminant;
	double				a;
	double				b;
	t_ray				*tmp;
	struct s_intersect	*head;

	head = NULL;
	tmp = transform(r, obj->inversed_transform);
	discriminant = calc_discriminant(&a, &b, tmp);
	destroy_ray(&tmp);
	if (discriminant < 0)
		return (NULL);
	discriminant = sqrtf(discriminant);
	add_back(&head, new_intersect((-b - discriminant) / (2 * a), obj));
	if (discriminant)
		add_back(&head, new_intersect((-b + discriminant) / (2 * a), obj));
	return (head);
}

struct s_intersect	*hit(struct s_intersect *head)
{
	struct s_intersect	*lower_non_negative;

	if (!head)
		return (NULL);
	lower_non_negative = head;
	while (head)
	{
		if (head->t > 0
			&& (lower_non_negative->t > head->t || lower_non_negative->t < 0))
			lower_non_negative = head;
		head = head->next;
	}
	if (lower_non_negative->t < 0)
		return (NULL);
	return (lower_non_negative);
}

// struct s_intersect	*intersect_world(struct s_world *w, t_ray *r)
// {
// 	struct s_intersect	*tmp;
// 	struct s_intersect	*head;

// 	head = NULL;
// 	tmp = w->intersections;
// 	while (tmp)
// 	{
// 		add_back(&head, intersect(tmp->obj, r));
// 		tmp = tmp->next;
// 	}
// 	bubblesort(&head);
// 	return (head);
// }