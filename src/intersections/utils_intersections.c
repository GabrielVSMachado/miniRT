/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:19:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/11 08:57:45 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <stdlib.h>

void	destroy_intersect(struct s_intersect **head)
{
	struct s_intersect	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		destroy_object(&(*head)->obj);
		free(*head);
		*head = NULL;
		*head = tmp;
	}
}

struct s_intersect	*new_intersect(double t, t_obj *obj)
{
	struct s_intersect	*result;

	result = malloc(sizeof(struct s_intersect));
	if (!result)
		return (NULL);
	result->t = t;
	result->obj = obj;
	result->next = NULL;
	return (result);
}

static struct s_intersect	*last_instersection(struct s_intersect *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

void	add_back(struct s_intersect **head, struct s_intersect *new)
{
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
		last_instersection(*head)->next = new;
}
