/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:50:57 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/11 16:06:16 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "tuples_utils.h"
# include "matrix.h"

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

t_ray	*ray(t_point origin, t_vector direction);
void	destroy_ray(t_ray	**r);
t_point	position(t_ray const *r, const float t);
t_ray	*transform(t_ray *r, t_matrix	*transform);
t_tuple	prod_matrix_tuple(t_matrix *m, t_tuple t);
#endif
