/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:41:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/23 18:36:22 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils_canvas.h"
#include <stdlib.h>

struct s_canvas	*render(t_camera *cam, struct s_world *w)
{
	struct s_canvas	*image;
	int				x;
	int				y;
	t_ray			*r;
	t_color			pixel_color;

	image = canvas(cam->hsize, cam->vsize);
	y = -1;
	while (++y < cam->vsize)
	{
		x = -1;
		while (++x < cam->hsize)
		{
			r = ray_for_pixel(cam, x, y);
			pixel_color = color_at(w, r);
			write_pixel(image, x, y, pixel_color);
			destroy_ray(&r);
			free(pixel_color);
		}
	}
	return (image);
}
