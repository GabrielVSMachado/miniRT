/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:54:19 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 18:22:34 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "../objects/object.h"
# include "../ray/raycast.h"

struct s_intersect
{
	double				t;
	t_obj				*obj;
	struct s_intersect	*next;
};

struct s_intersect	*intersect(t_obj *obj, t_ray *r);
struct s_intersect	*new_intersect(double t, t_obj *obj);
void				add_back(
						struct s_intersect **head, struct s_intersect *new
						);
void				destroy_intersect(struct s_intersect **head);
struct s_intersect	*hit(struct s_intersect *head);
#endif
