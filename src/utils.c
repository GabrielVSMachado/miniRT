/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:56:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:49:45 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

t_xs	*init_xs(void)
{
	t_xs	*head;

	head = malloc(sizeof(struct s_xs));
	if (!head)
		return (NULL);
	head->count = 0;
	head->fnode = NULL;
	return (head);
}
