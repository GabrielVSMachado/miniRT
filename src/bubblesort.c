/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:04:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/09 14:47:08 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <stdbool.h>

static t_intersect	*get_prevnode(t_intersect *fnode, t_intersect **node)
{
	while (fnode != *node && fnode->next != *node)
		fnode = fnode->next;
	return (fnode);
}

static void	swap(t_intersect **a, t_intersect **b, t_xs *head)
{
	t_intersect	*tmp;
	t_intersect	*prevnode;

	prevnode = get_prevnode(head->fnode, a);
	tmp = *a;
	*a = *b;
	tmp->next = (*a)->next;
	(*a)->next = tmp;
	if (head->fnode == prevnode && head->fnode->next != tmp)
		head->fnode = *a;
	else
		prevnode->next = *a;
}

void	bubblesort(t_xs *head)
{
	t_intersect	*i;
	bool		swaped;

	swaped = true;
	while (swaped)
	{
		swaped = false;
		i = head->fnode;
		while (i)
		{
			if (i->next && i->t > i->next->t)
			{
				swap(&i, &i->next, head);
				swaped = true;
			}
			i = i->next;
		}
	}
}
