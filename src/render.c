/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:41:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 23:35:48 by gvitor-s         ###   ########.fr       */
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

void	render(struct s_global *g)
{
	int				x;
	int				y;
	t_ray			*r;
	t_color			pixel_color;

	g->final_img = canvas(g->cam->hsize, g->cam->vsize);
	y = -1;
	while (++y < g->cam->vsize)
	{
		x = -1;
		while (++x < g->cam->hsize)
		{
			r = ray_for_pixel(g->cam, x, y);
			if (r)
			{
				pixel_color = color_at(g->world, r);
				write_pixel(g->final_img, x, y, pixel_color);
				free(pixel_color);
				destroy_ray(&r);
			}
		}
	}
	mlx_generate(g);
}
