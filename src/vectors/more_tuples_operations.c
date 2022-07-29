/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tuples_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:31 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/29 19:34:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vector	cross_product(t_vector v1, t_vector v2)
{
	return (
		vector(
			v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2],
			v1[0] * v2[1] - v1[1] * v2[0]
		)
	);
}

t_vector	normalize(t_tuple t)
{
	if (t[0] == 0 && t[1] == 0 && t[2] == 0)
		return (tuple(0, 0, 0, 0));
	return (scalar_multiplication(t, 1 / magnitude(t)));
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

t_tuple	prod_matrix_tuple(t_matrix *m, t_tuple t)
{
	double	tmp[4];
	int		row;

	row = -1;
	while (++row < 4)
	{
		tmp[row] = m->mtx[row][0] * t[0]
			+ m->mtx[row][1] * t[1]
			+ m->mtx[row][2] * t[2]
			+ m->mtx[row][3] * t[3];
	}
	return (tuple(tmp[0], tmp[1], tmp[2], tmp[3]));
}
