/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants_and_cofactors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:45:58 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:10:12 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vectors.h"
#include "utils.h"
#include "ft_stdlib.h"

inline double	determinant_2(t_matrix *m)
{
	return (m->mtx[0][0] * m->mtx[1][1] - m->mtx[1][0] * m->mtx[0][1]);
}

t_matrix	*submatrix(t_matrix *m, int line, int column)
{
	t_matrix					*sub;
	struct s_utils_submatrix	ut;

	sub = ft_calloc(sizeof(t_matrix), 1);
	if (!sub)
		return (NULL);
	sub->shape[0] = m->shape[0] - 1;
	sub->shape[1] = m->shape[1] - 1;
	ut.s_col = 0;
	ut.s_line = 0;
	ut.line = -1;
	while (++ut.line < (int)m->shape[0])
	{
		ut.column = -1;
		while (ut.line != line && ++ut.column < (int)m->shape[1])
		{
			if (ut.column == column)
				continue ;
			sub->mtx[ut.s_line][ut.s_col++] = m->mtx[ut.line][ut.column];
			ut.s_line += (ut.s_col == sub->shape[1]);
			ut.s_col = ut.s_col * (ut.s_col != sub->shape[1]);
		}
	}
	return (sub);
}

double	minor(t_matrix *m, int line, int column)
{
	t_matrix	*tmp;
	double		determinant;

	tmp = submatrix(m, line, column);
	determinant = determinant_2(tmp);
	free(tmp);
	return (determinant);
}

double	cofactor(t_matrix *m, int line, int column)
{
	double		dtm_of_minor;
	int			sum;
	t_matrix	*tmp;

	if (m->shape[0] == 4 && m->shape[1] == 4)
	{
		tmp = submatrix(m, line, column);
		dtm_of_minor = determinant(tmp);
		free(tmp);
	}
	else
		dtm_of_minor = minor(m, line, column);
	sum = line + column;
	return (dtm_of_minor * !(sum % 2) - dtm_of_minor * (sum % 2));
}

double	determinant(t_matrix *m)
{
	double	dtm;
	int		j;

	if (m->shape[0] == 2 && m->shape[1] == 2)
		return (determinant_2(m));
	dtm = 0;
	j = -1;
	while (++j < (int)m->shape[1])
		dtm += m->mtx[0][j] * cofactor(m, 0, j);
	return (dtm);
}
