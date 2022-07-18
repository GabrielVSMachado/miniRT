/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:30:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/17 13:49:35 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "matrix.h"
# include "raycast.h"

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	float		half_heigh;
	float		half_width;
	float		field_of_view;
	float		pixel_size;
	t_matrix	*tranform;
}	t_camera;

t_camera	*camera(int hsize, int vsize, float field_of_view);
t_ray		*ray_for_pixel(t_camera *cam, int x, int y);
void		transform_camera(t_camera *cam, t_matrix *tranform);
#endif
