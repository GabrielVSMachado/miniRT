/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:45:42 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/29 19:55:24 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "canvas.h"

struct s_canvas	*canvas(int width, int height)
{
	struct s_canvas	*img;

	img = malloc(sizeof(struct s_canvas));
	if (!img)
		return (NULL);
	img->img = ft_calloc(sizeof(unsigned int), width * height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->width = width;
	img->height = height;
	return (img);
}

void	write_pixel(struct s_canvas *cv, int x, int y, t_color color)
{
	unsigned char	c[4];
	int				i;

	if (x >= cv->width || y >= cv->height)
		return ;
	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0)
			color[i] = 0;
		else if (color[i] > 1)
			color[i] = 1;
	}
	c[2] = color[0] * 255;
	c[1] = color[1] * 255;
	c[0] = color[2] * 255;
	c[3] = 0;
	cv->img[y * cv->width + x] = *(unsigned int *)c;
}

t_color	pixel_at(struct s_canvas *cv, int x, int y)
{
	unsigned char	c[4];

	*(unsigned int *)c = cv->img[y * cv->width + x];
	return (color(c[2] / 255., c[1] / 255., c[0] / 255.));
}

void	destroy_canvas(struct s_canvas **cv)
{
	free((*cv)->img);
	free(*cv);
	*cv = NULL;
}
