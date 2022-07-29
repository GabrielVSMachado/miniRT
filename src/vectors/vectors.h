/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 22:08:56 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:55:47 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdbool.h>

typedef double *			t_tuple;
typedef const double		t_cordinate;
typedef t_tuple				t_point; // t_tuple with last value equal 1
typedef t_tuple				t_vector; // t_tuple with last value equal 0

typedef struct s_matrix
{
	unsigned int	shape[2];
	double			mtx[4][4];
}	t_matrix;

// Matrices Functions
t_matrix	*matrix(double form[][4], unsigned int shape[2]);
t_matrix	*matrices_product(t_matrix *m1, t_matrix *m2);
t_matrix	*tranposing(t_matrix *m);
t_matrix	*translate(t_cordinate x, t_cordinate y, t_cordinate z);
t_matrix	*scale(t_cordinate x, t_cordinate y, t_cordinate z);
t_matrix	*rotation_x(double rd);
t_matrix	*rotation_y(double rd);
t_matrix	*rotation_z(double rd);
t_matrix	*shearing(int value[6]);
t_matrix	*submatrix(t_matrix *m, int line, int column);
t_matrix	*inverse(t_matrix *m);
t_matrix	*identity(void);
double		determinant_2(t_matrix *m);
double		minor(t_matrix *m, int line, int column);
double		cofactor(t_matrix *m, int line, int column);
double		determinant(t_matrix *m);

// Tuple Functions
t_tuple		tuple(t_cordinate x, t_cordinate y, t_cordinate z,
				t_cordinate type);
t_point		point(t_cordinate x, t_cordinate y, t_cordinate z);
t_vector	vector(t_cordinate x, t_cordinate y, t_cordinate z);
t_tuple		add_tuples(t_tuple t1, t_tuple t2);
t_tuple		sub_tuple(t_tuple t1, t_tuple t2);
t_tuple		negate_tuple(t_tuple t);
t_tuple		scalar_multiplication(t_tuple t, double n);
t_vector	normalize(t_tuple t);
t_vector	cross_product(t_vector v1, t_vector v2);
double		magnitude(t_tuple v);
double		dot_product(t_vector v1, t_vector v2);
#endif
