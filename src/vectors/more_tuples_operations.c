/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tuples_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:31 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:34:40 by gvitor-s         ###   ########.fr       */
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
