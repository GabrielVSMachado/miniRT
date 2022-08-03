/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:04:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/03 00:16:12 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersections.h"
#include <stdbool.h>
#include <stdlib.h>

static void	swap(struct s_intersect **p, struct s_intersect **n)
{
	t_obj	*tmpo;
	double	tmpd;

	tmpd = (*p)->t;
	tmpo = (*p)->obj;
	(*p)->t = (*n)->t;
	(*p)->obj = (*n)->obj;
	(*n)->t = tmpd;
	(*n)->obj = tmpo;
}

void	bubblesort(struct s_intersect *head)
{
	bool				swaped;
	struct s_intersect	*tmp;
	struct s_intersect	*lptr;

	if (!head)
		return ;
	swaped = true;
	lptr = NULL;
	while (swaped)
	{
		swaped = false;
		tmp = head;
		while (tmp->next != lptr)
		{
			if (tmp->t > tmp->next->t)
			{
				swap(&tmp, &tmp->next);
				swaped = true;
			}
			tmp = tmp->next;
		}
		lptr = tmp;
	}
}
