/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:19:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/17 15:32:22 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_UTILS_H
# define TUPLES_UTILS_H

typedef const float *	t_tuple;
typedef const float		t_cordinate;
typedef t_tuple			t_point; // t_tuple with last value equal 1
typedef t_tuple			t_vector; // t_tuple with last value equal 0

t_tuple		tuple(t_cordinate x, t_cordinate y, t_cordinate z,
				t_cordinate type);
t_point		point(t_cordinate x, t_cordinate y, t_cordinate z);
t_vector	vector(t_cordinate x, t_cordinate y, t_cordinate z);
t_tuple		add_tuples(t_tuple t1, t_tuple t2);
t_tuple		sub_tuple(t_tuple t1, t_tuple t2);
t_tuple		negate_tuple(t_tuple t);
t_tuple		scalar_multiplication(t_tuple t, float n);
t_vector	normalize(t_tuple t);
t_vector	cross_product(t_vector v1, t_vector v2);
float		magnitude(t_tuple v);
float		dot_product(t_vector v1, t_vector v2);
#endif
