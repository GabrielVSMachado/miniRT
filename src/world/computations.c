/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:38:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 23:29:04 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../vectors/vectors.h"
#include "../intersections/intersections.h"

static void	cpyobjs(struct s_comps *comp, struct s_intersect *i)
{
	unsigned int		counter;
	t_matrix			*tmp;

	comp->obj->material->ambient = i->obj->material->ambient;
	comp->obj->material->diffuse = i->obj->material->diffuse;
	comp->obj->material->shininess = i->obj->material->shininess;
	comp->obj->material->specular = i->obj->material->specular;
	comp->obj->material->c[0] = i->obj->material->c[0];
	comp->obj->material->c[1] = i->obj->material->c[1];
	comp->obj->material->c[2] = i->obj->material->c[2];
	comp->obj->material->c[3] = i->obj->material->c[3];
	counter = 0;
	tmp = comp->obj->transform;
	while (counter < i->obj->transform->shape[0])
	{
		tmp->mtx[counter][0] = i->obj->transform->mtx[counter][0];
		tmp->mtx[counter][1] = i->obj->transform->mtx[counter][1];
		tmp->mtx[counter][2] = i->obj->transform->mtx[counter][2];
		tmp->mtx[counter][3] = i->obj->transform->mtx[counter][3];
		++counter;
	}
	tmp->shape[0] = i->obj->transform->shape[0];
	tmp->shape[1] = i->obj->transform->shape[1];
	comp->obj->inversed_transform = inverse(comp->obj->transform);
}

struct s_comps	*prepare_computations(struct s_intersect *i, t_ray *r)
{
	struct s_comps	*comput;
	t_tuple			tmp;

	comput = malloc(sizeof(struct s_comps));
	if (!comput)
		return (NULL);
	comput->t = i->t;
	comput->obj = new_object(i->obj->type);
	cpyobjs(comput, i);
	comput->point = position(r, comput->t);
	comput->eyev = negate_tuple(r->direction);
	comput->normalv = normal_at(comput->obj, comput->point);
	comput->inside = dot_product(comput->normalv, comput->eyev) < 0;
	comput->normalv[0] += -2.0 * comput->normalv[0] * (comput->inside == true);
	comput->normalv[1] += -2.0 * comput->normalv[1] * (comput->inside == true);
	comput->normalv[2] += -2.0 * comput->normalv[2] * (comput->inside == true);
	tmp = scalar_multiplication(comput->normalv, EPSILON);
	comput->over_point = add_tuples(comput->point, tmp);
	free(tmp);
	return (comput);
}

void	destroy_comps(struct s_comps **comps)
{
	destroy_object(&(*comps)->obj);
	free((*comps)->eyev);
	free((*comps)->point);
	free((*comps)->normalv);
	free((*comps)->over_point);
	free(*comps);
	*comps = NULL;
}
