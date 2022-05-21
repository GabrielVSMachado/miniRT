/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:10:21 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/19 17:11:09 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils_canvas.h"
#include <stdlib.h>
#include "utils_colors.h"

struct s_canvas	*canvas(int width, int height)
{
	struct s_canvas	*img;

	img = malloc(sizeof(struct s_canvas));
	if (!img)
		return (NULL);
	img->img = ft_memset(malloc(sizeof(unsigned int) * width * height),
			0, sizeof(unsigned int) * width * height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->width = width;
	img->height = height;
	img->line_lenght = sizeof(unsigned int) * width;
	return (img);
}

void	write_pixel(struct s_canvas *cv, int x, int y, t_color color)
{
	unsigned char	c[4];

	if (x >= cv->width || y >= cv->height)
		return ;
	c[2] = color[0] * 255;
	c[1] = color[1] * 255;
	c[0] = color[2] * 255;
	c[3] = 0;
	cv->img[y * cv->line_lenght + x] = *(unsigned int*)c;
}

t_color	pixel_at(struct s_canvas *cv, int x, int y)
{
	unsigned char	c[4];

	*(unsigned int*)c = cv->img[y * cv->line_lenght + x];
	return (color(c[2] / 255., c[1] / 255., c[0] / 255.));
}
