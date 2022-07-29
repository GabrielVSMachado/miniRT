/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:44:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:26:08 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>

t_matrix	*translate(t_cordinate x, t_cordinate y, t_cordinate z)
{
	return (
		matrix((double [][4]){
		{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}

t_matrix	*scale(t_cordinate x, t_cordinate y, t_cordinate z)
{
	return (
		matrix((double [][4]){
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}

t_matrix	*rotation_x(double rd)
{
	return (
		matrix((double [][4]){
		{1, 0, 0, 0},
		{0, cosf(rd), -sinf(rd), 0},
		{0, sinf(rd), cosf(rd), 0},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}

t_matrix	*rotation_y(double rd)
{
	return (
		matrix((double [][4]){
		{cosf(rd), 0, sinf(rd), 0},
		{0, 1, 0, 0},
		{-sinf(rd), 0, cosf(rd), 0},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}

t_matrix	*rotation_z(double rd)
{
	return (
		matrix((double [][4]){
		{cosf(rd), -sinf(rd), 0, 0},
		{sinf(rd), cosf(rd), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}, (unsigned int []){4, 4})
	);
}
