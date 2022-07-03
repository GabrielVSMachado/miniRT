/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 15:43:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/02 20:57:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "tuples_utils.h"
# include "utils_colors.h"
# include "material.h"

typedef struct s_point_light
{
	t_point	position;
	t_color	intensity;
}	t_light;

t_light				*point_light(t_color intensity, t_point position);
void				destroy_light(t_light **l);
t_color				lighting(
						struct s_material *m, t_light *l, t_point position,
						t_vector eye_normalv[2]);
#endif
