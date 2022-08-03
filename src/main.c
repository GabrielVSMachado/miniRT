/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:24:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/08 22:26:06 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "miniRT.h"

static void	copy_material(struct s_material *dst, struct s_material *src)
{
	dst->ambient = src->ambient;
	dst->diffuse = src->diffuse;
	dst->shininess = src->shininess;
	dst->specular = src->specular;
	memcpy(dst->c, src->c, sizeof(double) * 4);
}

static t_obj	*my_floor(void)
{
	t_obj	*f = new_object(SPHERE);
	calc_linear_transformation(f, scale(10, 0.1, 10));
	f->material->specular = 0;
	f->material->c[1] = 0.9;
	f->material->c[2] = 0.9;
	f->inversed_transform = inverse(f->transform);
	return f;
}

static	t_obj	*left_wall(struct s_material *m)
{
	t_obj	*lwall = new_object(SPHERE);
	calc_linear_transformation(lwall, scale(10, 0.1, 10));
	calc_linear_transformation(lwall, rotation_x(M_PI_2));
	calc_linear_transformation(lwall, rotation_y(-M_PI_4));
	calc_linear_transformation(lwall, translate(0, 0, 5));
	copy_material(lwall->material, m);
	lwall->inversed_transform = inverse(lwall->transform);
	return lwall;
}

static	t_obj	*right_wall(struct s_material *m)
{
	t_obj	*rwall = new_object(SPHERE);
	calc_linear_transformation(rwall, scale(10, 0.1, 10));
	calc_linear_transformation(rwall, rotation_x(M_PI_2));
	calc_linear_transformation(rwall, rotation_y(M_PI_4));
	calc_linear_transformation(rwall, translate(0, 0, 5));
	copy_material(rwall->material, m);
	rwall->inversed_transform = inverse(rwall->transform);
	return rwall;
}

static t_obj	*middle_sphere(void)
{
	t_obj	*middle = new_object(SPHERE);
	calc_linear_transformation(middle, translate(-0.5, 1, 0.5));
	middle->material->diffuse = 0.7;
	middle->material->specular = 0.3;
	middle->material->c[0] = .1;
	middle->material->c[2] = .5;
	middle->inversed_transform = inverse(middle->transform);
	return middle;
}

static t_obj	*right_obj(void)
{
	t_obj	*rsphere = new_object(SPHERE);
	calc_linear_transformation(rsphere, scale(0.5, .5, .5));
	calc_linear_transformation(rsphere, translate(1.5, .5, -.5));
	rsphere->material->diffuse = 0.7;
	rsphere->material->specular = .3;
	rsphere->material->c[0] = .5;
	rsphere->material->c[2] = .1;
	rsphere->inversed_transform = inverse(rsphere->transform);
	return rsphere;
}

static t_obj	*left_obj(void)
{
	t_obj	*lsphere = new_object(SPHERE);
	calc_linear_transformation(lsphere, scale(0.33, 0.33, 0.33));
	calc_linear_transformation(lsphere, translate(-1.5, 0.33, -0.75));
	lsphere->material->diffuse = 0.7;
	lsphere->material->specular = 0.3;
	lsphere->material->c[1] = 0.8;
	lsphere->material->c[2] = 0.1;
	lsphere->inversed_transform = inverse(lsphere->transform);
	return lsphere;
}

static t_camera	*cam(void)
{
	t_camera	*c = camera(800, 600, M_PI / 3.);
	transform_camera(c, view_transformation(
		point(0, 1.5, -5),
		point(0, 1, 0),
		vector(0, 1, 0)
	));
	return c;
}

static	struct s_intersect	*add_to_world(t_obj *objects[], int nsphere)
{
	struct s_intersect	*head = NULL;

	for (int i = 0; i < nsphere; i++)
		add_back(&head, new_intersect(0, objects[i]));
	
	return head;
}

struct data
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*addr;
	int		endian;
	int		bpp;
	int		line_lenght;
};

static	void	pass_to_mlx_image(struct data *dst, struct s_canvas *src)
{
	for (int i = 0; i < src->height; i++)
	{
		for (int j = 0; j < src->width; j++)
		{
			*(unsigned int *)(dst->addr + (i * dst->line_lenght + j * (dst->bpp / 8))) = src->img[i * src->width + j];
		}
	}
}


int	main(void)
{
	t_obj	*f = my_floor();
	t_obj	*rwall = right_wall(f->material);
	t_obj	*lwall = left_wall(f->material);
	t_obj	*rsphere = right_obj();
	t_obj	*lsphere = left_obj();
	t_obj	*middle = middle_sphere();
	struct s_intersect		*head = add_to_world((t_obj *[]){f, rwall, lwall, lsphere, middle, rsphere}, 6);
	t_light		*light = point_light(color(1, 1, 1), point(-10, 10, -10));
	t_camera	*_camera  = cam();
	struct	s_world		*world = init_world(light, head);
	struct s_canvas	*image = render(_camera, world);
	struct data		dt;

	dt.mlx = mlx_init();
	dt.img = mlx_new_image(dt.mlx, image->width, image->height);
	dt.addr = mlx_get_data_addr(dt.img, &dt.bpp, &dt.line_lenght, &dt.endian);
	dt.win = mlx_new_window(dt.mlx, image->width, image->height, "miniRT");
	pass_to_mlx_image(&dt, image);
	mlx_put_image_to_window(dt.mlx, dt.win, dt.img, 0, 0);
	mlx_loop(dt.mlx);
	return 0;
}
