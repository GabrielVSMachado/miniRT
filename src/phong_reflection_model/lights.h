/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:43:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 19:14:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include <stdbool.h>
# include "../canvas/canvas.h"
# include "../vectors/vectors.h"

typedef struct s_point_light
{
	t_point	position;
	t_color	intensity;
}	t_light;

struct s_utils_lighting
{
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		effective_color;
	t_vector	lightv;
	t_vector	reflectv;
	double		light_dot_normal;
	double		reflect_dot_eye;
};

struct s_parameters_lighting
{
	struct s_material	*material;
	t_light				*light;
	t_point				position;
	t_vector			eyev;
	t_vector			normalv;
	bool				in_shadow;	
};

void		destroy_light(t_light **l);
t_vector	reflect(t_vector velocity, t_vector normal);
t_light		*point_light(t_color intensity, t_point position);
t_color		lighting(struct s_parameters_lighting *p);

#endif
