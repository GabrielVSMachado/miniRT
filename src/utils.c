/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:56:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 16:00:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

#define EPISLON 0.00001

bool	assert_float_eq(const float f1, const float f2)
{
	if (fabsf(f1 - f2) < EPISLON)
		return (true);
	return (false);
}

void	destroy_matrix(t_matrix **m)
{
	int	_;

	_ = -1;
	while (++_ < (int)(*m)->shape[0])
		free((void *)(*m)->mtx[_]);
	free((*m)->mtx);
	free(*m);
}
