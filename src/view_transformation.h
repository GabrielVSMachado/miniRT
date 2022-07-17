/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transformation.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:43:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/16 13:43:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_TRANSFORMATION_H
# define VIEW_TRANSFORMATION_H

# include "matrix.h"
# include "tuples_utils.h"

struct s_utils_view_transformation
{
	t_point		forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	*orientation;
	t_matrix	*view_transformed;
	t_matrix	*translation;
};

t_matrix	*view_transformation(t_point from, t_point to, t_vector up);
#endif
