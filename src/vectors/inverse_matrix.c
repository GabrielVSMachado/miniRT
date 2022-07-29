/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:24:17 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:10:58 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vectors.h"

static inline t_matrix	*cofactor_matrix(t_matrix *m, double (*f)())
{
	return (matrix((double [][4]){
		{f(m, 0, 0), f(m, 0, 1), f(m, 0, 2), f(m, 0, 3)},
		{f(m, 1, 0), f(m, 1, 1), f(m, 1, 2), f(m, 1, 3)},
		{f(m, 2, 0), f(m, 2, 1), f(m, 2, 2), f(m, 2, 3)},
		{f(m, 3, 0), f(m, 3, 1), f(m, 3, 2), f(m, 3, 3)}},
		m->shape)
		);
}

static inline double	s(t_matrix *transpost_cofactor, double determinant,
	int line, int column)
{
	return (transpost_cofactor->mtx[line][column] * determinant);
}

t_matrix	*inverse(t_matrix *m)
{
	t_matrix	*cm;
	t_matrix	*tc;
	t_matrix	*inversed;
	double		dt;

	dt = determinant(m);
	if (!dt)
		return (NULL);
	cm = cofactor_matrix(m, cofactor);
	tc = tranposing(cm);
	dt = 1 / dt;
	inversed = matrix((double [][4]){
		{s(tc, dt, 0, 0), s(tc, dt, 0, 1), s(tc, dt, 0, 2), s(tc, dt, 0, 3)},
		{s(tc, dt, 1, 0), s(tc, dt, 1, 1), s(tc, dt, 1, 2), s(tc, dt, 1, 3)},
		{s(tc, dt, 2, 0), s(tc, dt, 2, 1), s(tc, dt, 2, 2), s(tc, dt, 2, 3)},
		{s(tc, dt, 3, 0), s(tc, dt, 3, 1), s(tc, dt, 3, 2), s(tc, dt, 3, 3)}
		}, m->shape);
	free(cm);
	free(tc);
	return (inversed);
}
