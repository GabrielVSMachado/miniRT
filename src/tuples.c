/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:35:53 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/05 20:00:09 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tuples_utils.h"

t_tuple	tuple(t_cordinate x, t_cordinate y, t_cordinate z, t_cordinate type)
{
	float	*tpe;

	tpe = malloc(sizeof(float) * 4);
	if (!tpe)
		return (NULL);
	tpe[0] = x;
	tpe[1] = y;
	tpe[2] = z;
	tpe[3] = type;
	return (tpe);
}

t_point	point(t_cordinate x, t_cordinate y, t_cordinate z)
{
	return (tuple(x, y, z, 1));
}

t_vector	vector(t_cordinate x, t_cordinate y, t_cordinate z)
{
	return (tuple(x, y, z, 0));
}

t_vector	normalize(t_tuple t)
{
	return (scalar_multiplication(t, 1 / magnitude(t)));
}

float	dot_product(t_vector v1, t_vector v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}
