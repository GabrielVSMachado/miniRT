/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:41:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 19:21:01 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../vectors/vectors.h"
# include "../canvas/canvas.h"

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

struct s_material
{
	t_color	c;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
};

struct s_material	*material(void);
void				destroy_material(struct s_material **m);
t_obj				*new_object(unsigned int type);
void				destroy_object(t_obj **obj);
void				calc_linear_transformation(t_obj *obj, t_matrix *transform);
t_vector			normal_at(t_obj *obj, t_point world_point);
#endif