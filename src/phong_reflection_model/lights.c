/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:20:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:38:06 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "lights.h"
#include "../objects/object.h"
#include "../canvas/canvas.h"

t_vector	reflect(t_vector velocity, t_vector normal)
{
	t_tuple		tmp;
	t_vector	result;

	tmp = scalar_multiplication(normal, 2. * dot_product(velocity, normal));
	result = sub_tuple(velocity, tmp);
	free(tmp);
	return (result);
}

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
			light->intensity[0] * material->objc[0] * material->envc[0],
			light->intensity[1] * material->objc[1] * material->envc[1],
			light->intensity[2] * material->objc[2] * material->envc[2]);
	util->ambient = scalar_multiplication(
			util->effective_color, material->ambient);
	util->diffuse = color(0, 0, 0);
	util->specular = color(0, 0, 0);
}

static void	calc_diffuse_and_specular(struct s_utils_lighting *util,
		struct s_parameters_lighting *p)
{
	t_tuple	tmp;

	free(util->diffuse);
	util->diffuse = scalar_multiplication(
			util->effective_color,
			p->material->diffuse * util->light_dot_normal
			);
	tmp = negate_tuple(util->lightv);
	util->reflectv = reflect(tmp, p->normalv);
	util->reflect_dot_eye = dot_product(util->reflectv, p->eyev);
	free(tmp);
	if (util->reflect_dot_eye > 0)
	{
		free(util->specular);
		util->specular = scalar_multiplication(
				p->light->intensity,
				pow(util->reflect_dot_eye, p->material->shininess)
				* p->material->specular
				);
	}
}

t_color	lighting(struct s_parameters_lighting *p)
{
	struct s_utils_lighting	util;
	t_vector				tmp;
	t_color					result;

	if (p->in_shadow)
		return (color_when_in_shadown(p));
	init_variables(&util, p->light, p->material);
	tmp = sub_tuple(p->light->position, p->position);
	util.lightv = normalize(tmp);
	util.light_dot_normal = dot_product(util.lightv, p->normalv);
	if (util.light_dot_normal >= 0)
		calc_diffuse_and_specular(&util, p);
	free(tmp);
	tmp = add_tuples(util.ambient, util.diffuse);
	result = add_tuples(tmp, util.specular);
	return (free(tmp), destroy_used_memory(&util), result);
}
