/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:07:23 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/05 22:29:24 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "intersections.h"
# include "lights.h"
# include "raycast.h"

struct s_world
{
	t_xs		*obj;
	t_light		*light_src;
};

struct s_world	*init_world(t_light *light, t_xs *head);
t_xs			*intersect_world(struct s_world *w, t_ray *r);
#endif
