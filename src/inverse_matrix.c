/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:24:17 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/05 13:54:06 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"
#include <stdlib.h>

static t_matrix	*cofactor_matrix(t_matrix *m)
{
	int			i;
	int			j;
	t_matrix	*cm;

	cm = matrix((t_tuple []){NULL, NULL, NULL, NULL},
			(unsigned int []){m->shape[0], m->shape[1]});
	i = -1;
	while (++i < (int)m->shape[0])
	{
		j = -1;
		cm->mtx[i] = tuple(0, 0, 0, 0);
		while (++j < (int)m->shape[1])
			cm->mtx[i][j] = cofactor(m, i, j);
	}
	return (cm);
}

t_matrix	*inverse(t_matrix *m)
{
	t_matrix	*cm;
	t_matrix	*tcm;
	t_matrix	*inversed;
	int			i;
	double		dtm;

	dtm = determinant(m);
	if (!dtm)
		return (NULL);
	cm = cofactor_matrix(m);
	tcm = tranposing(cm);
	inversed = matrix((t_tuple []){NULL, NULL, NULL, NULL},
			(unsigned int []){m->shape[0], m->shape[1]});
	dtm = 1 / dtm;
	i = -1;
	while (++i < (int)inversed->shape[1])
		inversed->mtx[i] = scalar_multiplication(tcm->mtx[i], dtm);
	destroy_matrix(&cm);
	destroy_matrix(&tcm);
	return (inversed);
}
