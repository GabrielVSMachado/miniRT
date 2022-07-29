/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:45:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/29 19:56:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "../vectors/vectors.h"

typedef t_tuple	t_color;

struct s_canvas
{
	unsigned int	*img;
	int				width;
	int				height;
};

// canvas functions
struct s_canvas	*canvas(int width, int height);
void			write_pixel(struct s_canvas *cv, int x, int y, t_color color);
t_color			pixel_at(struct s_canvas *cv, int x, int y);
void			destroy_canvas(struct s_canvas **cv);

// Colors functions
t_color			color(const double r, const double g, const double b);
t_color			add_colors(t_color c1, t_color c2);
t_color			sub_colors(t_color c1, t_color c2);
t_color			colors_product(t_color c1, t_color c2);
#endif