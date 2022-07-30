/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:24:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 18:24:48 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include <stdlib.h>

t_light	*point_light(t_color intensity, t_point position)
{
	t_light	*l;

	l = malloc(sizeof(struct s_point_light));
	if (!l)
		return (NULL);
	l->intensity = intensity;
	l->position = position;
	return (l);
}

void	destroy_light(t_light **l)
{
	if (*l)
	{
		free((*l)->intensity);
		free((*l)->position);
		free(*l);
		*l = NULL;
	}
}
