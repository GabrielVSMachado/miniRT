/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:20:41 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/19 00:16:05 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../vectors/vectors.h"
# include "../canvas/canvas.h"
# include "../ray/raycast.h"

struct s_material
{
	t_color		objc;
	t_color		envc;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
};

typedef struct s_cylinder
{
	double	min;
	double	max;
}	t_cylinder;

typedef struct s_object
{
	unsigned int		type;
	t_matrix			*transform;
	t_matrix			*inversed_transform;
	struct s_material	*material;
	t_cylinder			attributes_cy;
	struct s_intersect	*(*local_intersect)(struct s_object *obj, t_ray *r);
	double				*(*local_normal_at)(struct s_object *obj, t_point p);
}	t_obj;

enum	e_type_obj
{
	PLANE = 1,
	SPHERE,
	CYLINDER
};

struct s_material	*material(
						t_color obj_color, t_color env_color, double ambient);
t_obj				*new_object(unsigned int type);
void				destroy_material(struct s_material **m);
void				destroy_object(t_obj **obj);
void				get_l_transformation(t_obj *obj, t_matrix *transform);
t_vector			sphere_normal_at(t_obj *sphere, t_point point);
t_vector			plane_normal_at(t_obj *plane, t_point point);
t_vector			cylinder_normal_at(t_obj *cylinder, t_point point);
struct s_intersect	*plane_intersect(t_obj *plane, t_ray *r);
struct s_intersect	*sphere_intersect(t_obj *obj, t_ray *r);
struct s_intersect	*cylinder_intersect(t_obj *cylinder, t_ray *r);
t_obj				*new_cylinder(void);
t_obj				*new_sphere(void);
t_obj				*new_plane(void);
struct s_intersect	*intersect_caps(t_obj *cylinder, t_ray *r);
#endif
