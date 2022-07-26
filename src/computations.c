/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:38:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/25 21:13:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "world.h"
#include <ft_string.h>
#include <stdlib.h>

static void	cpyobjs(struct s_comps *comp, t_intersect *i)
{
	unsigned int		counter;
	t_matrix			*tmp;

	comp->obj->m->ambient = i->obj->m->ambient;
	comp->obj->m->diffuse = i->obj->m->diffuse;
	comp->obj->m->shininess = i->obj->m->shininess;
	comp->obj->m->specular = i->obj->m->specular;
	ft_memcpy(comp->obj->m->c, i->obj->m->c, sizeof(float) * 4);
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
}

struct s_comps	*prepare_computations(t_intersect *i, t_ray *r)
{
	struct s_comps	*comput;
	t_tuple			tmp;

	comput = malloc(sizeof(struct s_comps));
	if (!comput)
		return (NULL);
	comput->t = i->t;
	comput->obj = sphere();
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
	destroy_sphere(&(*comps)->obj);
	free((*comps)->eyev);
	free((*comps)->point);
	free((*comps)->normalv);
	free((*comps)->over_point);
	free(*comps);
	*comps = NULL;
}
