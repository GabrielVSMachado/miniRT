/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:54:19 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/16 22:23:16 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "sphere.h"

typedef struct s_intersect
{
	double				t;
	int					typeobj;
	t_sphere			*obj;
	struct s_intersect	*next;
}	t_intersect;

typedef struct s_xs
{
	unsigned int		count;
	struct s_intersect	*fnode;
}	t_xs;

enum	e_type_obj
{
	PLANE = 1,
	SPHERE,
	CYLINDER
};

void		intersect(t_sphere *s, t_ray *r, t_xs *head);
t_intersect	*intersection(double t, t_sphere *obj);
void		intersections(t_xs *head, t_intersect *new);
void		destroy_intersections(t_xs **head);
t_intersect	*hit(t_xs *head);
t_xs		*init_xs(void);
#endif
