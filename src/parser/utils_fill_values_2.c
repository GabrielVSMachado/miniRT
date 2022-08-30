/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fill_values_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:14:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/26 17:21:03 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_parser.h"
#include "../objects/object.h"
#include "../canvas/canvas.h"
#include "ft_stdlib.h"
#include <math.h>
#include "../intersections/intersections.h"

struct s_intersect	*get_values_cylinder(
	char **content, t_color	envc, double intensity_env
	)
{
	t_obj		*new;
	t_vector	nv;
	t_vector	center;
	double		xy_lenght;

	new = new_cylinder();
	new->material = material(get_color(content[5]),
			color(envc[0], envc[1], envc[2]), intensity_env);
	nv = get_vector(content[2]);
	center = get_vector(content[1]);
	new->attributes_cy.max = ft_atod(content[4]) / 2.;
	new->attributes_cy.min = -ft_atod(content[4]) / 2.;
	xy_lenght = sqrt(pow(nv[0], 2) + pow(nv[1], 2));
	get_l_transformation(new, translate(center[0], center[1], center[2]));
	get_l_transformation(new, scale(
			ft_atod(content[3]) / 2., 1, ft_atod(content[3]) / 2.));
	get_l_transformation(new, rotation_x(acos(xy_lenght)));
	if (xy_lenght == 0)
		get_l_transformation(new, rotation_z(M_PI_2));
	else
		get_l_transformation(new, rotation_z(acos(nv[1] / xy_lenght)));
	free(nv);
	free(center);
	new->inversed_transform = inverse(new->transform);
	return (new_intersect(0, new));
}

struct s_intersect	*get_values_plane(
	char **content, t_color envc, double intensity_env)
{
	t_obj		*new;
	t_vector	center;
	t_vector	nv;
	double		xy_lenght;

	new = new_plane();
	new->material = material(
			get_color(content[3]),
			color(envc[0], envc[1], envc[2]), intensity_env);
	center = get_vector(content[1]);
	nv = get_vector(content[2]);
	xy_lenght = sqrt(pow(nv[0], 2) + pow(nv[1], 2));
	get_l_transformation(new, translate(center[0], center[1], center[2]));
	get_l_transformation(new, rotation_x(acos(xy_lenght)));
	if (xy_lenght == 0)
		get_l_transformation(new, rotation_z(M_PI_2));
	else
		get_l_transformation(new, rotation_z(acos(nv[1] / xy_lenght)));
	new->material->specular = 0;
	free(nv);
	free(center);
	new->inversed_transform = inverse(new->transform);
	return (new_intersect(0, new));
}
