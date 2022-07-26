/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:34:52 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/25 21:17:04 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTATIONS_H
# define COMPUTATIONS_H

# include "tuples_utils.h"
# include "sphere.h"
# include "intersections.h"
# define EPSILON 0.0001

struct s_comps
{
	float		t;
	t_sphere	*obj;
	t_point		point;
	t_point		over_point;
	t_vector	eyev;
	t_vector	normalv;
	bool		inside;
};

void			destroy_comps(struct s_comps **comps);
struct s_comps	*prepare_computations(t_intersect *i, t_ray *r);
#endif
