/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:54:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/02 15:10:11 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples_utils.h"
#include <stdlib.h>

t_vector	reflect(t_vector velocity, t_vector normal)
{
	t_tuple		tmp;
	t_vector	result;

	tmp = scalar_multiplication(normal, 2. * dot_product(velocity, normal));
	result = sub_tuple(velocity, tmp);
	free(tmp);
	return (result);
}
