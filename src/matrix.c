/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:54:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 16:04:24 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "miniRT.h"

void	destroy_matrix(t_matrix **m)
{
	int	_;

	_ = -1;
	while (++_ < (int)(*m)->shape[0])
		free((void *)(*m)->mtx[_]);
	free((*m)->mtx);
	free(*m);
}

t_matrix	*matrix(t_tuple form[], unsigned int shape[2])
{
	t_matrix	*m;
	int			i;

	m = (t_matrix *)malloc(sizeof(t_matrix));
	if (!m)
		return (NULL);
	m->mtx = malloc(sizeof(t_tuple) * shape[0]);
	if (!m->mtx)
		return (free(m), NULL);
	i = -1;
	while (++i < (int)shape[0])
		m->mtx[i] = form[i];
	m->shape[0] = shape[0];
	m->shape[1] = shape[1];
	return (m);
}

bool	assert_t_matrix_eq(t_matrix const *m1, t_matrix const *m2)
{
	int	i;
	int	j;

	if (m1->shape[0] != m2->shape[0]
		|| m1->shape[1] != m2->shape[1])
		return (false);
	i = -1;
	while (++i < (int)m1->shape[0])
	{
		j = -1;
		while (++j < (int)m2->shape[1])
			if (!assert_float_eq(m1->mtx[i][j], m2->mtx[i][j]))
				return (false);
	}
	return (true);
}

static float	calc_line_column_sigma(t_matrix const *m1,
		t_matrix const *m2, int line, int column)
{
	int		i;
	float	total;

	i = -1;
	total = 0;
	while (++i < (int)m1->shape[1])
		total += m1->mtx[line][i] * m2->mtx[i][column];
	return (total);
}

t_matrix	*matrixs_product(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*prd;
	int			i;
	int			j;

	if (m1->shape[1] != m2->shape[0])
		return (NULL);
	prd = matrix((t_tuple []){NULL, NULL, NULL, NULL},
			(unsigned int []){m1->shape[0], m2->shape[1]});
	i = -1;
	while (++i < (int)prd->shape[0])
	{
		prd->mtx[i] = tuple(0, 0, 0, 0);
		j = -1;
		while (++j < (int)prd->shape[1])
			((float *)prd->mtx[i])[j] = calc_line_column_sigma(m1, m2, i, j);
	}
	return (prd);
}
