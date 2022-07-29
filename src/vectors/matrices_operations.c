/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:10:07 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/29 00:01:05 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <stdlib.h>

t_matrix	*shearing(int value[6])
{
	return (
		matrix((double [][4]){
		{1, value[0], value[1], 0},
		{value[2], 1, value[3], 0},
		{value[4], value[5], 1, 0},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}

t_matrix	*tranposing(t_matrix *m)
{
	return (
		matrix((double [][4]){
		{m->mtx[0][0], m->mtx[1][0], m->mtx[2][0], m->mtx[3][0]},
		{m->mtx[0][1], m->mtx[1][1], m->mtx[2][1], m->mtx[3][1]},
		{m->mtx[0][2], m->mtx[1][2], m->mtx[2][2], m->mtx[3][2]},
		{m->mtx[0][3], m->mtx[1][3], m->mtx[2][3], m->mtx[3][3]}},
		(unsigned int []){m->shape[1], m->shape[0]})
		);
}

t_matrix	*identity(void)
{
	return (
		matrix((double [][4]){
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}

static inline double	c(t_matrix const *m1, t_matrix const *m2,
	int line, int column)
{
	return (
		m1->mtx[line][0] * m2->mtx[0][column]
		+ m1->mtx[line][1] * m2->mtx[1][column]
		+ m1->mtx[line][2] * m2->mtx[2][column]
		+ m1->mtx[line][3] * m2->mtx[3][column]
	);
}

t_matrix	*matrices_product(t_matrix *m1, t_matrix *m2)
{
	if (m1->shape[1] != m2->shape[0])
		return (NULL);
	return (matrix((double [][4]){
		{c(m1, m2, 0, 0), c(m1, m2, 0, 1), c(m1, m2, 0, 2), c(m1, m2, 0, 3)},
		{c(m1, m2, 1, 0), c(m1, m2, 1, 1), c(m1, m2, 1, 2), c(m1, m2, 1, 3)},
		{c(m1, m2, 2, 0), c(m1, m2, 2, 1), c(m1, m2, 2, 2), c(m1, m2, 2, 3)},
		{c(m1, m2, 3, 0), c(m1, m2, 3, 1), c(m1, m2, 3, 2), c(m1, m2, 3, 3)}
	}, (unsigned int []){m1->shape[0], m2->shape[1]})
	);
}
