/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:38:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/11 19:49:35 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "world.h"
#include <ft_string.h>
#include <stdlib.h>

struct s_comps	*prepare_computations(t_intersect *i, t_ray *r)
{
	struct s_comps	*comput;

	comput = malloc(sizeof(struct s_comps));
	if (!comput)
		return (NULL);
	comput->t = i->t;
	comput->obj = ft_memcpy(sphere(), i->obj, sizeof(t_sphere));
	comput->point = position(r, comput->t);
	comput->eyev = negate_tuple(r->direction);
	comput->normalv = normal_at(comput->obj, comput->point);
	comput->inside = dot_product(comput->eyev, comput->normalv) < 0;
	comput->normalv[0] += -2 * comput->normalv[0] * (comput->inside == true);
	comput->normalv[1] += -2 * comput->normalv[1] * (comput->inside == true);
	comput->normalv[2] += -2 * comput->normalv[2] * (comput->inside == true);
	return (comput);
}

void	destroy_comps(struct s_comps **comps)
{
	destroy_sphere(&(*comps)->obj);
	free((*comps)->eyev);
	free((*comps)->point);
	free((*comps)->normalv);
	free(*comps);
	*comps = NULL;
}
