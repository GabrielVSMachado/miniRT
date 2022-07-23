/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:57:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/23 18:34:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadows.h"
#include <stdlib.h>
#include <stdbool.h>

bool	in_shadowed(struct s_world *w, t_point p)
{
	bool		result;
	t_vector	tmp;
	t_ray		*shadow_ray;
	t_xs		*head;
	t_intersect	*hit_point;

	tmp = sub_tuple(w->light_src->position, p);
	shadow_ray = ray(point(p[0], p[1], p[2]), normalize(tmp));
	head = intersect_world(w, shadow_ray);
	hit_point = hit(head);
	result = (hit_point && hit_point->t < magnitude(tmp));
	destroy_ray(&shadow_ray);
	destroy_intersections(&head);
	free(tmp);
	return (result);
}
