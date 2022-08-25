/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:41:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:24:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"
#include <unistd.h>

void	error(struct s_global *g)
{
	write(2, "Error\n", 6);
	destroy_global(g);
	exit(1);
}

void	destroy_global(struct s_global *g)
{
	destroy_camera(&g->cam);
	destroy_world(&g->world);
	destroy_canvas(&g->final_img);
}

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
