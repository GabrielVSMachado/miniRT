/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:06:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 00:46:55 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../miniRT.h"
#include <unistd.h>
#include <stdlib.h>

#define ESC 0xff1b

static int	key_hook(int key, void *pg)
{
	struct s_global	*g;

	g = pg;
	if (key == ESC)
	{
		mlx_destroy_image(g->data.mlx, g->data.dimg.img);
		mlx_destroy_window(g->data.mlx, g->data.window);
		mlx_destroy_display(g->data.mlx);
		free(g->data.mlx);
		destroy_world(&g->world);
		destroy_camera(&g->cam);
		destroy_canvas(&g->final_img);
		exit(0);
	}
	return (0);
}

static int	put_again_img(void *pg)
{
	struct s_global	*g;

	g = pg;
	mlx_put_image_to_window(
		g->data.mlx, g->data.window, g->data.dimg.img, 0, 0);
	return (0);
}

void	register_hooks(struct s_global *g)
{
	mlx_key_hook(g->data.window, key_hook, g);
	mlx_expose_hook(g->data.window, put_again_img, g);
}
