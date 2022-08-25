/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fill_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:58:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:32:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../canvas/canvas.h"
#include "ft_string.h"
#include "utils_parser.h"
#include "../camera/camera.h"
#include "../phong_reflection_model/lights.h"
#include <math.h>
#include "../miniRT.h"

t_color	get_color(char *_color)
{
	char	**values;
	t_color	result;

	values = ft_split(_color, ',');
	if (!values)
		return (NULL);
	result = color(
			ft_atod(values[0]) / 255.,
			ft_atod(values[1]) / 255.,
			ft_atod(values[2]) / 255.
			);
	destroy_content(values);
	return (result);
}

t_vector	get_vector(char *vector_)
{
	t_vector	v;
	char		**splited;

	splited = ft_split(vector_, ',');
	if (!splited)
		return (NULL);
	v = vector(ft_atod(splited[0]), ft_atod(splited[1]), ft_atod(splited[2]));
	destroy_content(splited);
	return (v);
}

t_light	*get_values_light(char **content)
{
	t_light	*l;
	double	intensity;

	intensity = ft_atod(content[2]);
	l = point_light(
			color(intensity, intensity, intensity),
			get_vector(content[1])
			);
	l->position[3] = 1.;
	return (l);
}

t_camera	*get_values_camera(char **content)
{
	t_camera	*cam;
	t_point		from;
	t_point		to;
	t_vector	up;
	t_vector	tmp;

	from = get_vector(content[1]);
	from[3] = 0.;
	to = get_vector(content[2]);
	tmp = cross_product((double []){0, 1, 0, 0}, to);
	up = cross_product(tmp, to);
	cam = camera(WIDTH, HEIGHT, ft_atod(content[3]) * (M_PI / 180.));
	transform_camera(cam, view_transformation(from, to, up));
	free(from);
	free(tmp);
	free(to);
	free(up);
	return (cam);
}

struct s_intersect	*get_values_sphere(
	char **content, t_color envc, double intensity_env)
{
	t_obj	*new;
	double	r;

	new = new_sphere();
	r = ft_atod(content[2]) / 2.;
	new->material = material(
			get_color(content[3]),
			color(envc[0], envc[1], envc[2]), intensity_env);
	calc_linear_transformation(new, scale(r, r, r));
	calc_linear_transformation(new,
		translate(
			ft_atod(content[1]), ft_atod(content[2]), ft_atod(content[3]))
		);
	return (new_intersect(0, new));
}
