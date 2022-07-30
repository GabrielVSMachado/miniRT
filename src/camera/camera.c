/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:30:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 12:39:04 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>
#include <stdlib.h>

t_camera	*camera(int hsize, int vsize, double field_of_view)
{
	t_camera	*new;
	double		half_view;
	double		aspect;

	new = (t_camera *)malloc(sizeof(struct s_camera));
	if (!new)
		return (NULL);
	new->hsize = hsize;
	new->vsize = vsize;
	new->field_of_view = field_of_view;
	half_view = tanf(new->field_of_view / 2.);
	aspect = (double)new->hsize / new->vsize;
	new->half_heigh = (aspect >= 1) * (half_view / aspect)
		+ (aspect < 1) * half_view;
	new->half_width = (aspect >= 1) * half_view
		+ (aspect < 1) * (aspect * half_view);
	new->pixel_size = (new->half_width * 2) / new->hsize;
	new->tranform = identity();
	return (new);
}

void	transform_camera(t_camera *cam, t_matrix *tranform)
{
	t_matrix	*tmp;

	tmp = matrices_product(tranform, cam->tranform);
	free(cam->tranform);
	cam->tranform = tmp;
}

inline static t_tuple	fn(t_matrix *m, t_tuple toclean)
{
	t_tuple	result;

	result = prod_matrix_tuple(m, toclean);
	free(toclean);
	return (result);
}

t_ray	*ray_for_pixel(t_camera *cam, int x, int y)
{
	t_tuple		pixel;
	t_point		origin;
	t_vector	direction;
	t_matrix	*inversed_transform;
	t_point		util;

	inversed_transform = inverse(cam->tranform);
	origin = fn(inversed_transform, point(0, 0, 0));
	pixel = fn(inversed_transform,
			point(
				cam->half_width - (x + 0.5) * cam->pixel_size,
				cam->half_heigh - (y + 0.5) * cam->pixel_size,
				-1
				)
			);
	util = sub_tuple(pixel, origin);
	direction = normalize(util);
	free(util);
	free(pixel);
	free(inversed_transform);
	return (ray(origin, direction));
}

void	destroy_camera(t_camera **cam)
{
	free((*cam)->tranform);
	free((*cam));
	*cam = NULL;
}
