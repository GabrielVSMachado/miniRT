/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 15:06:54 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_COLORS_H
# define UTILS_COLORS_H

# include "tuples_utils.h"

typedef t_tuple	t_color;

t_color	color(const float r, const float g, const float b);
t_color	add_colors(t_color c1, t_color c2);
t_color	sub_colors(t_color c1, t_color c2);
t_color	colors_product(t_color c1, t_color c2);
#endif
