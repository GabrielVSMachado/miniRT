/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:41:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 14:06:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../vectors/vectors.h"
# include "material.h"

typedef struct s_object
{
	unsigned int		type;
	t_matrix			*transform;
	t_matrix			*inversed_transform;
	struct s_material	*material;
}	t_obj;

enum	e_type_obj
{
	PLANE = 1,
	SPHERE,
	CYLINDER
};

t_obj		*new_object(unsigned int type);
void		destroy_object(t_obj **obj);
void		calc_linear_transformation(t_obj	*obj, t_matrix *transform);
t_vector	normal_at(t_obj *obj, t_point world_point);
#endif