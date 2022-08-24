/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:03:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/22 23:58:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "camera.h"

static inline void	destroy_utils(struct s_utils_view_transformation *ut)
{
	free(ut->orientation);
	free(ut->translation);
	free(ut->left);
	free(ut->true_up);
	free(ut->forward);
}

t_matrix	*view_transformation(t_point from, t_point to, t_vector up)
{
	struct s_utils_view_transformation	ut;
	t_vector							tmp;

	tmp = sub_tuple(to, from);
	ut.forward = normalize(tmp);
	free(tmp);
	tmp = normalize(up);
	ut.left = cross_product(ut.forward, tmp);
	free(tmp);
	ut.true_up = cross_product(ut.left, ut.forward);
	ut.orientation = matrix((double [][4]){
		{ut.left[0], ut.left[1], ut.left[2], 0},
		{ut.true_up[0], ut.true_up[1], ut.true_up[2], 0},
		{-ut.forward[0], -ut.forward[1], -ut.forward[2], 0},
		{0, 0, 0, 1}
		}, (unsigned int []){4, 4});
	ut.translation = translate(-from[0], -from[1], -from[2]);
	ut.view_transformed = matrices_product(ut.orientation, ut.translation);
	destroy_utils(&ut);
	return (ut.view_transformed);
}
