/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:19:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 15:19:28 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "tuples_utils.h"

typedef struct s_matrix
{
	t_tuple			*mtx;
	unsigned int	shape[2];

}	t_matrix;

t_matrix	*matrix(t_tuple form[], unsigned int shape[2]);
void		destroy_matrix(t_matrix **M);
#endif
