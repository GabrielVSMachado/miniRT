/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:56:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/30 16:00:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

#define EPISLON 0.00001

bool	assert_float_eq(const float f1, const float f2)
{
	if (fabsf(f1 - f2) < EPISLON)
		return (true);
	return (false);
}
