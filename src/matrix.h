/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:19:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/06 14:29:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "tuples_utils.h"
# include <stdbool.h>

typedef struct s_matrix
{
	t_tuple			*mtx;
	unsigned int	shape[2];

}	t_matrix;

t_matrix	*matrix(t_tuple form[], unsigned int shape[2]);
t_matrix	*matrixs_product(t_matrix *m1, t_matrix *m2);
t_matrix	*tranposing(t_matrix *m);
t_matrix	*scalating(t_cordinate x, t_cordinate y, t_cordinate z);
t_matrix	*rotation_x(float rd);
t_matrix	*rotation_y(float rd);
t_matrix	*rotation_z(float rd);
t_matrix	*submatrix(t_matrix *m, int line, int column);
t_matrix	*inverse(t_matrix *m);
t_matrix	*translation(t_cordinate x, t_cordinate y, t_cordinate z);
t_matrix	*mpoint(t_cordinate	x, t_cordinate y, t_cordinate z);
float		determinant_2(t_matrix *m);
float		minor(t_matrix *m, int line, int column);
float		cofactor(t_matrix *m, int line, int column);
float		determinant(t_matrix *m);
void		destroy_matrix(t_matrix **M);
bool		assert_t_matrix_eq(t_matrix const *m1, t_matrix const *m2);
#endif
