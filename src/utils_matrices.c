/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:45:58 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/03 17:25:55 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"
#include <stdlib.h>
#include <string.h>

float	determinant_2(t_matrix *m)
{
	return (m->mtx[0][0] * m->mtx[1][1] - m->mtx[1][0] * m->mtx[0][1]);
}

t_matrix	*submatrix(t_matrix *m, int line, int column)
{
	t_matrix	*sub;
	int			indexs[2];
	int			subindex[2];

	sub = matrix((t_tuple []){NULL, NULL, NULL, NULL},
			(unsigned int []){m->shape[0] - 1, m->shape[1] - 1});
	if (!sub)
		return (NULL);
	indexs[0] = -1;
	memset(subindex, 0, sizeof(int) * 2);
	while (++indexs[0] < (int)m->shape[0])
	{
		indexs[1] = -1;
		while (indexs[0] != line && ++indexs[1] < (int)m->shape[1])
		{
			if (indexs[1] == column)
				continue ;
			if (!sub->mtx[subindex[0]])
				sub->mtx[subindex[0]] = tuple(0, 0, 0, 0);
			sub->mtx[subindex[0]][subindex[1]++] = m->mtx[indexs[0]][indexs[1]];
			subindex[0] += (subindex[1] == (int)sub->shape[1]);
			subindex[1] = subindex[1] * (subindex[1] != (int)sub->shape[1]);
		}
	}
	return (sub);
}
