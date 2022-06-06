/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:44:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/06 15:17:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix	*translation(t_cordinate x, t_cordinate y, t_cordinate z)
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
