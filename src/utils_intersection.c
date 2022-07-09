/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:19:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/05 22:44:59 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <stdlib.h>

void	destroy_intersections(t_xs **head)
{
	t_intersect	*tmp;

	while (*head && (*head)->fnode)
	{
		tmp = (*head)->fnode->next;
		free((*head)->fnode);
		(*head)->fnode = NULL;
		(*head)->fnode = tmp;
	}
	free(*head);
	*head = NULL;
}

t_intersect	*intersection(float t, t_sphere *obj)
{
	t_intersect	*result;

	result = malloc(sizeof(t_intersect));
	if (!result)
		return (NULL);
	result->t = t;
	result->obj = obj;
	result->next = NULL;
	return (result);
}
