/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:03:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/17 12:20:20 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "tuples_utils.h"
#include "view_transformation.h"
#include <stdlib.h>

t_matrix	*view_transformation(t_point from, t_point to, t_vector up)
{
	struct s_utils_view_transformation	utils;
	t_vector							tmp;

	tmp = sub_tuple(to, from);
	utils.forward = normalize(tmp);
	free(tmp);
	tmp = normalize(up);
	utils.left = cross_product(utils.forward, tmp);
	free(tmp);
	utils.true_up = cross_product(utils.left, utils.forward);
	tmp = utils.forward;
	utils.forward = negate_tuple(utils.forward);
	free(tmp);
	utils.orientation = matrix(
			(t_tuple []){utils.left, utils.true_up, utils.forward,
			tuple(0, 0, 0, 1)},
			(unsigned int []){4, 4}
			);
	utils.translation = translate(-from[0], -from[1], -from[2]);
	utils.view_transformed = matrices_product(
			utils.orientation, utils.translation);
	destroy_matrix(&utils.orientation);
	destroy_matrix(&utils.translation);
	return (utils.view_transformed);
}
