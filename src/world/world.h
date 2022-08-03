/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 22:07:23 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/02 22:54:55 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# define EPSILON 0.0001

# include <stdbool.h>
# include "../ray/raycast.h"
# include "../objects/object.h"
# include "../intersections/intersections.h"
# include "../phong_reflection_model/lights.h"

struct s_world
{
	struct s_intersect	*intersections;
	t_light				*light_src;
};

struct s_comps
{
	double		t;
	t_obj		*obj;
	t_point		point;
	t_point		over_point;
	t_vector	eyev;
	t_vector	normalv;
	bool		inside;
};

struct s_intersect	*intersect_world(struct s_world *world, t_ray *r);
struct s_comps		*prepare_computations(struct s_intersect *i, t_ray *r);
struct s_world		*init_world(t_light *light, struct s_intersect *head);
t_color				shade_hit(struct s_world *w, struct s_comps *comps);
t_color				color_at(struct s_world *w, t_ray *r);
void				destroy_world(struct s_world **world);
void				destroy_comps(struct s_comps **comps);
#endif
