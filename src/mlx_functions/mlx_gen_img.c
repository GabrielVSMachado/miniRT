/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_gen_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 23:18:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:48:55 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include "utils_mlx.h"
#include "../miniRT.h"
#include "../canvas/canvas.h"

void	register_hooks(struct s_global *g);

static void	generate_img(struct s_global *g)
{
	g->data.dimg.img = mlx_new_image(g->data.dimg.img, WIDTH, HEIGHT);
	if (!g->data.dimg.img)
	{
		mlx_destroy_display(g->data.mlx);
		free(g->data.mlx);
		error(g);
	}
	g->data.dimg.addr = mlx_get_data_addr(
			g->data.dimg.img,
			&g->data.dimg.bpp,
			&g->data.dimg.line_lenght,
			&g->data.dimg.endian
			);
}

static void	fill_img(struct s_data *data, struct s_canvas *rendered_img)
{
	int		i;
	int		j;
	char	*dstf;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			dstf = data->dimg.addr + (
					i * data->dimg.line_lenght + j * (data->dimg.bpp / 8)
					);
			*(unsigned int *)dstf = rendered_img->img[
				i * rendered_img->height + j
			];
		}
	}
}

void	mlx_generate(void *pg)
{
	struct s_global	*g;

	g = pg;
	g->data.mlx = mlx_init();
	if (!g->data.mlx)
		error(g);
	generate_img(g);
	g->data.window = mlx_new_window(g->data.mlx, WIDTH, HEIGHT, "miniRT");
	if (!g->data.window)
	{
		mlx_destroy_image(g->data.mlx, g->data.dimg.img);
		mlx_destroy_display(g->data.mlx);
		free(g->data.mlx);
		error(g);
	}
	fill_img(&g->data, g->final_img);
	mlx_put_image_to_window(
		g->data.mlx, g->data.window, g->data.dimg.img, 0, 0);
	register_hooks(g);
	mlx_loop(g->data.mlx);
}
