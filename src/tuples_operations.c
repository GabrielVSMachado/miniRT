/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:07:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 15:07:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples_utils.h"
#include <stdlib.h>
#include <math.h>

t_tuple	add_tuples(t_tuple t1, t_tuple t2)
{
	return (tuple(t1[0] + t2[0], t1[1] + t2[1], t1[2] + t2[2], t1[3] + t2[3]));
}

t_tuple	sub_tuple(t_tuple t1, t_tuple t2)
{
	return (tuple(t1[0] - t2[0], t1[1] - t2[1], t1[2] - t2[2], t1[3] - t2[3]));
}

t_tuple	negate_tuple(t_tuple t)
{
	return (tuple(-t[0], -t[1], -t[2], -t[3]));
}

t_tuple	scalar_multiplication(t_tuple t, float n)
{
	return (tuple(t[0] * n, t[1] * n, t[2] * n, t[3] * n));
}

float	magnitude(t_tuple v)
{
	return (sqrtf(powf(v[0], 2) + powf(v[1], 2) + powf(v[2], 2)));
}
