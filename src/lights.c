/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:20:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/24 13:43:55 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include "material.h"
#include "miniRT.h"
#include "tuples_utils.h"
#include "utils_colors.h"
#include <math.h>
#include <stdlib.h>

static void	destroy_used_memory(struct s_utils_lighting *util)
{
	free(util->ambient);
	free(util->diffuse);
	free(util->effective_color);
	free(util->specular);
	free(util->lightv);
	free(util->reflectv);
}

static void	init_variables(struct s_utils_lighting *util, t_light *light,
		struct s_material *material)
{
	util->lightv = NULL;
	util->reflectv = NULL;
	util->light_dot_normal = 0;
	util->reflect_dot_eye = 0;
	util->effective_color = color(
			light->intensity[0] * material->c[0],
			light->intensity[1] * material->c[1],
			light->intensity[2] * material->c[2]
			);
	util->ambient = scalar_multiplication(
			util->effective_color,
			material->ambient);
	util->diffuse = color(0, 0, 0);
	util->specular = color(0, 0, 0);
}

t_color	lighting(struct s_parameters_lighting *p)
{
	struct s_utils_lighting	util;
	t_vector				tmp;
	t_color					result;

	if (p->in_shadow)
		return (color(p->m->ambient, p->m->ambient, p->m->ambient));
	init_variables(&util, p->light, p->m);
	tmp = sub_tuple(p->light->position, p->position);
	util.lightv = normalize(tmp);
	util.light_dot_normal = dot_product(util.lightv, p->normalv);
	if (free(tmp), util.light_dot_normal >= 0)
	{
		free(util.diffuse);
		util.diffuse = scalar_multiplication(util.effective_color, p->m->diffuse * util.light_dot_normal);
		tmp = negate_tuple(util.lightv);
		util.reflectv = reflect(tmp, p->normalv);
		util.reflect_dot_eye = dot_product(util.reflectv, p->eyev);
		if (util.reflect_dot_eye > 0)
		{
			free(util.specular);
			util.specular = scalar_multiplication(p->light->intensity,
					powf(util.reflect_dot_eye, p->m->shininess) * p->m->specular);
		}
	}
	tmp = add_tuples(util.ambient, util.diffuse);
	result = add_tuples(tmp, util.specular);
	return (free(tmp), destroy_used_memory(&util), result);
}

t_light	*point_light(t_color intensity, t_point position)
{
	t_light	*l;

	l = malloc(sizeof(struct s_point_light));
	if (!l)
		return (NULL);
	l->intensity = intensity;
	l->position = position;
	return (l);
}

void	destroy_light(t_light **l)
{
	if (*l)
	{
		free((*l)->intensity);
		free((*l)->position);
		free(*l);
		*l = NULL;
	}
}
