/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:24:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:46:30 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include <stdlib.h>
#include "../canvas/canvas.h"

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

t_color	color_when_in_shadown(struct s_parameters_lighting *p)
{
	return (
		color(
			p->material->ambient * p->material->objc[0] * p->material->envc[0],
			p->material->ambient * p->material->objc[1] * p->material->envc[1],
			p->material->ambient * p->material->objc[2] * p->material->envc[2])
	);
}
