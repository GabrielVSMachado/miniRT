/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:53:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/09 23:44:23 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "intersections.h"
#include "../ray/raycast.h"
#include "../world/world.h"

void	cpymatrices(t_matrix *dst, t_matrix *src)
{
	int	counter;

	counter = -1;
	while (++counter < (int)src->shape[0])
	{
		dst->mtx[counter][0] = src->mtx[counter][0];
		dst->mtx[counter][1] = src->mtx[counter][1];
		dst->mtx[counter][2] = src->mtx[counter][2];
		dst->mtx[counter][3] = src->mtx[counter][3];
	}
	dst->shape[0] = src->shape[0];
	dst->shape[1] = src->shape[1];
}

t_obj	*cpyobj(t_obj *src)
{
	t_obj	*cpy;

	cpy = new_object(src->type);
	cpy->material->ambient = src->material->ambient;
	cpy->material->diffuse = src->material->diffuse;
	cpy->material->shininess = src->material->shininess;
	cpy->material->specular = src->material->specular;
	cpy->material->c[0] = src->material->c[0];
	cpy->material->c[1] = src->material->c[1];
	cpy->material->c[2] = src->material->c[2];
	cpy->material->c[3] = src->material->c[3];
	cpymatrices(cpy->transform, src->transform);
	cpy->inversed_transform = malloc(sizeof(t_matrix));
	cpymatrices(cpy->inversed_transform, src->inversed_transform);
	cpy->_intersect = src->_intersect;
	cpy->_normal_at = src->_normal_at;
	return (cpy);
}

static double	calc_discriminant(double *a, double *b, t_ray *r)
{
	double	c;

	*a = dot_product(r->direction, r->direction);
	*b = 2 * dot_product(r->direction, r->origin);
	c = dot_product(r->origin, r->origin) - 1;
	return (pow(*b, 2) - 4 * (*a) * c);
}

// TODO: Thinking as solve de problem to destroy objects without create copys
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
	discriminant = sqrt(discriminant);
	add_back(&head, new_intersect((-b - discriminant) / (2 * a), cpyobj(obj)));
	if (discriminant)
		add_back(&head, new_intersect(
				(-b + discriminant) / (2 * a), cpyobj(obj)));
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
