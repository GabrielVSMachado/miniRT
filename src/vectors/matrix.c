/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:54:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/27 23:37:41 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vectors.h"
#include "ft_stdlib.h"

static void	set_values_for_matrix(t_matrix *m, double form[][4])
{
	int			i;
	int			j;

	i = -1;
	while (++i < (int)m->shape[0])
	{
		j = -1;
		while (++j < (int)m->shape[1])
			m->mtx[i][j] = form[i][j];
		while (m->shape[1] < 4 && j < 4)
			m->mtx[i][j++] = 0;
	}
	while (m->shape[0] < 4 && i < 4)
	{
		m->mtx[i][0] = 0;
		m->mtx[i][1] = 0;
		m->mtx[i][2] = 0;
		m->mtx[i][3] = 0;
		i++;
	}
}

t_matrix	*matrix(double form[][4], unsigned int shape[2])
{
	t_matrix	*m;

	m = (t_matrix *)malloc(sizeof(t_matrix));
	if (!m)
		return (NULL);
	m->shape[0] = shape[0];
	m->shape[1] = shape[1];
	set_values_for_matrix(m, form);
	return (m);
}
