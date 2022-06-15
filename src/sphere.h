/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:02:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/11 18:29:23 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "raycast.h"
# include "tuples_utils.h"

typedef struct s_sphere
{
	t_point			center;
	unsigned int	r;
}	t_sphere;

typedef struct s_xs
{
	unsigned int	count;
	float			psec[2];
}	t_xs;

t_xs		*intersect(t_sphere *s, t_ray *r);
t_sphere	*sphere(void);
#endif
