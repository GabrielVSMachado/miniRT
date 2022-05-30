/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:54:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/28 20:54:30 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"
#include <stdlib.h>
#include <string.h>

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
	m->mtx = memset(malloc(sizeof(t_tuple) * shape[0]), 0,
			sizeof(t_tuple) * shape[0]);
	if (!m->mtx)
		return (free(m), NULL);
	i = -1;
	while (++i < (int)shape[0])
		m->mtx[i] = form[i];
	m->shape[0] = shape[0];
	m->shape[1] = shape[1];
	return (m);
}
