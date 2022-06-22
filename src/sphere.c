/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:58:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/16 13:55:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include <stdlib.h>
#include "matrix.h"

t_sphere	*sphere(void)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	s->transform = identity();
	return (s);
}

void	destroy_sphere(t_sphere **s)
{
	destroy_matrix(&(*s)->transform);
	free(*s);
	*s = NULL;
}

void	set_transform(t_sphere *s, t_matrix *t)
{
	t_matrix	*product;

	product = matrices_product(t, s->transform);
	destroy_matrix(&s->transform);
	s->transform = product;
}
