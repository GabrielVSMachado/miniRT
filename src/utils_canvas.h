/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_canvas.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:42 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 15:06:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_CANVAS_H
# define UTILS_CANVAS_H

# include "utils_colors.h"

struct s_canvas
{
	unsigned int	*img;
	int				width;
	int				height;
};

struct s_canvas	*canvas(int width, int height);
void			write_pixel(struct s_canvas *cv, int x, int y, t_color color);
t_color			pixel_at(struct s_canvas *cv, int x, int y);
#endif
