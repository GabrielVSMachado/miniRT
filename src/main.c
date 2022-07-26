/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:24:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/25 21:42:52 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_canvas.h"
#include "mlx.h"
#include "view_transformation.h"
#include "render.h"
#include "world.h"
#include "tuples_utils.h"
#include "shadows.h"
#include "lights.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "camera.h"

static void	copy_material(struct s_material *dst, struct s_material *src)
{
	dst->ambient = src->ambient;
	dst->diffuse = src->diffuse;
	dst->shininess = src->shininess;
	dst->specular = src->specular;
	memcpy(dst->c, src->c, sizeof(double) * 4);
}

static t_sphere	*my_floor(void)
{
	t_sphere	*f = sphere();
	set_transform(f, scale(10, 0.1, 10));
	f->m->specular = 0;
	f->m->c[1] = 0.9;
	f->m->c[2] = 0.9;
	f->inverse_transform = inverse(f->transform);
	return f;
}

static	t_sphere	*left_wall(struct s_material *m)
{
	t_sphere	*lwall = sphere();
	set_transform(lwall, scale(10, 0.1, 10));
	set_transform(lwall, rotation_x(M_PI_2));
	set_transform(lwall, rotation_y(-M_PI_4));
	set_transform(lwall, translate(0, 0, 5));
	copy_material(lwall->m, m);
	lwall->inverse_transform = inverse(lwall->transform);
	return lwall;
}

static	t_sphere	*right_wall(struct s_material *m)
{
	t_sphere	*rwall = sphere();
	set_transform(rwall, scale(10, 0.1, 10));
	set_transform(rwall, rotation_x(M_PI_2));
	set_transform(rwall, rotation_y(M_PI_4));
	set_transform(rwall, translate(0, 0, 5));
	copy_material(rwall->m, m);
	rwall->inverse_transform = inverse(rwall->transform);
	return rwall;
}

static t_sphere	*middle_sphere(void)
{
	t_sphere	*middle = sphere();
	set_transform(middle, translate(-0.5, 1, 0.5));
	middle->m->diffuse = 0.7;
	middle->m->specular = 0.3;
	middle->m->c[0] = .1;
	middle->m->c[2] = .5;
	middle->inverse_transform = inverse(middle->transform);
	return middle;
}

static t_sphere	*right_sphere(void)
{
	t_sphere	*rsphere = sphere();
	set_transform(rsphere, scale(0.5, .5, .5));
	set_transform(rsphere, translate(1.5, .5, -.5));
	rsphere->m->diffuse = 0.7;
	rsphere->m->specular = .3;
	rsphere->m->c[0] = .5;
	rsphere->m->c[2] = .1;
	rsphere->inverse_transform = inverse(rsphere->transform);
	return rsphere;
}

static t_sphere	*left_sphere(void)
{
	t_sphere	*lsphere = sphere();
	set_transform(lsphere, scale(0.33, 0.33, 0.33));
	set_transform(lsphere, translate(-1.5, 0.33, -0.75));
	lsphere->m->diffuse = 0.7;
	lsphere->m->specular = 0.3;
	lsphere->m->c[1] = 0.8;
	lsphere->m->c[2] = 0.1;
	lsphere->inverse_transform = inverse(lsphere->transform);
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

static	t_xs	*add_to_world(t_sphere *objects[], int nsphere)
{
	t_xs	*head = init_xs();

	for (int i = 0; i < nsphere; i++)
		intersections(head, intersection(0, objects[i]));
	
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
	t_sphere	*f = my_floor();
	t_sphere	*rwall = right_wall(f->m);
	t_sphere	*lwall = left_wall(f->m);
	t_sphere	*rsphere = right_sphere();
	t_sphere	*lsphere = left_sphere();
	t_sphere	*middle = middle_sphere();
	t_xs		*head = add_to_world((t_sphere *[]){f, rwall, lwall, lsphere, middle, rsphere}, 6);
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
