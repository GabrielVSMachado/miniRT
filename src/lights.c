/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:20:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/02 21:32:08 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include "material.h"
#include "miniRT.h"
#include "tuples_utils.h"
#include "utils_colors.h"
#include <math.h>
#include <stdlib.h>

static void	destroy_used_memory(t_color *adse, t_vector *lrtv)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(adse[i]);
	i = -1;
	while (++i < 3)
		free(lrtv[i]);
}

static void	init_variables(t_color *adse, t_light *light,
		struct s_material *material, t_vector *lrtv)
{
	lrtv[0] = NULL;
	lrtv[1] = NULL;
	lrtv[2] = NULL;
	adse[3] = color(
			light->intensity[0] * material->c[0],
			light->intensity[1] * material->c[1],
			light->intensity[2] * material->c[2]
			);
	adse[0] = scalar_multiplication(adse[3], material->ambient);
	adse[1] = color(0, 0, 0);
	adse[2] = color(0, 0, 0);
}

t_color	lighting(
		struct s_material *m,
		t_light	*l,
		t_point position, t_vector eye_normalv[2])
{
	t_color		adser[5];
	float		dot[2];
	t_vector	lrtv[3];

	init_variables(adser, l, m, lrtv);
	lrtv[2] = sub_tuple(l->position, position);
	lrtv[0] = normalize(lrtv[2]);
	dot[0] = dot_product(lrtv[0], eye_normalv[1]);
	if (free(lrtv[2]), dot[0] >= 0)
	{
		free(adser[1]);
		adser[1] = scalar_multiplication(adser[3], m->diffuse * dot[0]);
		lrtv[2] = negate_tuple(lrtv[0]);
		lrtv[1] = reflect(lrtv[2], eye_normalv[1]);
		dot[1] = dot_product(lrtv[1], eye_normalv[0]);
		if (dot[1] > 0)
		{
			free(adser[2]);
			adser[2] = scalar_multiplication(l->intensity,
					powf(dot[1], m->shininess) * m->specular);
		}
	}
	lrtv[2] = add_tuples(adser[0], adser[1]);
	adser[4] = add_tuples(lrtv[2], adser[2]);
	return (destroy_used_memory(adser, lrtv), adser[4]);
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
	free((*l)->intensity);
	free((*l)->position);
	free(*l);
	*l = NULL;
}
