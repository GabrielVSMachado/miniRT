/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:04:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 23:00:23 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <stdbool.h>

static struct s_intersect	*get_prev(
	struct s_intersect *head, struct s_intersect **node)
{
	while (head != *node && head->next != *node)
		head = head->next;
	return (head);
}

static void	swap(struct s_intersect **p, struct s_intersect **n,
	struct s_intersect *head)
{
	struct s_intersect	*prev;
	struct s_intersect	*tmp;

	prev = get_prev(head, p);
	if (prev != *p)
	{
		tmp = (*n)->next;
		(*n)->next = *p;
		prev->next = *n;
		(*p)->next = tmp;
	}
	else
	{
		tmp = (*n)->next;
		(*n)->next = *p;
		(*p)->next = tmp;
	}
}

void	bubblesort(struct s_intersect *head)
{
	bool				swaped;
	struct s_intersect	*tmp;

	swaped = true;
	while (swaped)
	{
		swaped = false;
		tmp = head;
		while (tmp)
		{
			if (tmp->next && tmp->t > tmp->next->t)
			{
				swap(&tmp, &tmp->next, head);
				swaped = true;
			}
			tmp = tmp->next;
		}
	}
}
