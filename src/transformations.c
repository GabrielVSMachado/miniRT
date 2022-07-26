/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:44:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/08 15:47:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"
#include <math.h>

t_matrix	*translate(t_cordinate x, t_cordinate y, t_cordinate z)
{
	return (
		matrix((t_tuple []){
			tuple(1, 0, 0, x),
			tuple(0, 1, 0, y),
			tuple(0, 0, 1, z),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}

t_matrix	*scale(t_cordinate x, t_cordinate y, t_cordinate z)
{
	return (
		matrix((t_tuple []){
			tuple(x, 0, 0, 0),
			tuple(0, y, 0, 0),
			tuple(0, 0, z, 0),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}

t_matrix	*rotation_x(double rd)
{
	return (
		matrix((t_tuple []){
			tuple(1, 0, 0, 0),
			tuple(0, cosf(rd), -sinf(rd), 0),
			tuple(0, sinf(rd), cosf(rd), 0),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}

t_matrix	*rotation_y(double rd)
{
	return (
		matrix((t_tuple []){
			tuple(cosf(rd), 0, sinf(rd), 0),
			tuple(0, 1, 0, 0),
			tuple(-sinf(rd), 0, cosf(rd), 0),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}

t_matrix	*rotation_z(double rd)
{
	return (
		matrix((t_tuple []){
			tuple(cosf(rd), -sinf(rd), 0, 0),
			tuple(sinf(rd), cosf(rd), 0, 0),
			tuple(0, 0, 1, 0),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}
