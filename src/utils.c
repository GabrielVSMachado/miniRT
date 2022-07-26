/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:56:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/25 21:38:03 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "intersections.h"
#include "matrix.h"
#include "tuples_utils.h"

#define EPISLON 0.00001

bool	assert_double_eq(const double f1, const double f2)
{
	return (fabs(f1 - f2 ) < EPISLON);
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

t_matrix	*mpoint(t_cordinate	x, t_cordinate y, t_cordinate z)
{
	return (
		matrix((t_tuple []){
			tuple(x, 0, 0, 0),
			tuple(y, 0, 0, 0),
			tuple(z, 0, 0, 0),
			tuple(1, 0, 0, 0)
		}, (unsigned int []){4, 1})
	);
}

t_matrix	*identity(void)
{
	return (
		matrix((t_tuple []){
			tuple(1, 0, 0, 0),
			tuple(0, 1, 0, 0),
			tuple(0, 0, 1, 0),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}

t_xs	*init_xs(void)
{
	t_xs	*head;

	head = malloc(sizeof(struct s_xs));
	if (!head)
		return (NULL);
	head->count = 0;
	head->fnode = NULL;
	return (head);
}
