/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:35:53 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/04 20:31:59 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

const float	*tuple(const float x, const float y, const float z,
		const float type)
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

const float	*point(const float x, const float y, const float z)
{
	return (tuple(x, y, z, 1));
}

const float	*vector(const float x, const float y, const float z)
{
	return (tuple(x, y, z, 0));
}
