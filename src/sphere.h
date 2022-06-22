/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:02:29 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/06/16 13:55:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "raycast.h"
# include "tuples_utils.h"

typedef struct s_sphere
{
	t_matrix		*transform;
}	t_sphere;

t_sphere	*sphere(void);
void		destroy_sphere(t_sphere **s);
void		set_transform(t_sphere *s, t_matrix *t);
#endif
