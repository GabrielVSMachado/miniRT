/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:45:54 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/29 19:56:16 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

t_color	color(const double r, const double g, const double b)
{
	return (tuple(r, g, b, -1));
}

t_color	add_colors(t_color c1, t_color c2)
{
	return (add_tuples(c1, c2));
}

t_color	sub_colors(t_color c1, t_color c2)
{
	return (sub_tuple(c1, c2));
}

t_color	colors_product(t_color c1, t_color c2)
{
	return (color(c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]));
}
