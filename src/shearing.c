/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <42.fr>                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:31:20 by marvin            #+#    #+#             */
/*   Updated: 2022/06/08 14:34:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"

t_matrix	*shearing(int value[6])
{
	return (
		matrix((t_tuple []){
			tuple(1, value[0], value[1], 0),
			tuple(value[2], 1, value[3], 0),
			tuple(value[4], value[5], 1, 0),
			tuple(0, 0, 0, 1)
		}, (unsigned int []){4, 4})
	);
}
