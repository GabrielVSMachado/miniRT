/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/09 13:04:28 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "tuples_utils.h"
# include "intersections.h"

t_vector	reflect(t_vector velocity, t_vector normal);
bool		assert_double_eq(const double f1, const double f2);
void		bubblesort(t_xs *head);
#endif
