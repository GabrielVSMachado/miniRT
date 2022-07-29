/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:20 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:34:55 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vectors.h"

t_tuple	tuple(t_cordinate x, t_cordinate y, t_cordinate z, t_cordinate type)
{
	double	*tpe;

	tpe = malloc(sizeof(double) * 4);
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
