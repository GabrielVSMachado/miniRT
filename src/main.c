/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:24:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/13 22:22:18 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "miniRT.h"

static t_obj	*my_floor(void)
{
	t_obj	*f = new_object(PLANE);
	f->material->specular = 0;
	f->material->c[1] = 0.5;
	f->material->c[2] = 0.5;
	f->inversed_transform = identity();
	return f;
}

static t_obj	*backdrop(void)
{
	t_obj	*lwall = new_object(PLANE);
	calc_linear_transformation(lwall, rotation_x(-M_PI / 2.));
	calc_linear_transformation(lwall, translate(0, 0, 10));
	lwall->inversed_transform = inverse(lwall->transform);
	lwall->material->c[1] = 0.9;
	lwall->material->c[2] = 0.9;
	lwall->material->specular = 0;
	return lwall;
}

// static t_obj	*right_wall(void)
// {
// 	t_obj	*rwall = new_object(PLANE);
// 	calc_linear_transformation(rwall, rotation_x(M_PI_2));
// 	calc_linear_transformation(rwall, rotation_y(M_PI / 4));
// 	calc_linear_transformation(rwall, translate(5, 0, 0));
// 	rwall->inversed_transform = inverse(rwall->transform);
// 	rwall->material->c[1] = 0.9;
// 	rwall->material->c[2] = 0.9;
// 	rwall->material->specular = 0;
// 	return rwall;
// }

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

static t_obj	*cylinder(void)
{
	t_obj	*cylinder = new_object(CYLINDER);
	calc_linear_transformation(cylinder, scale(0.33, 0.33, 0.33));
	calc_linear_transformation(cylinder, translate(-1.5, 0.33, -0.75));
	cylinder->material->diffuse = 0.7;
	cylinder->material->specular = 0.3;
	cylinder->material->c[1] = 0.8;
	cylinder->material->c[2] = 0.1;
	cylinder->inversed_transform = inverse(cylinder->transform);
	return cylinder;
}

static t_camera	*cam(void)
{
	t_tuple		ftu[] = {
		point(0, 1.5, -7),
		point(2, 1, 0),
		vector(0, 1, 0)
	};
	t_matrix	*view = view_transformation(ftu[0], ftu[1], ftu[2]);
	free(ftu[0]);
	free(ftu[1]);
	free(ftu[2]);
	t_camera	*c = camera(800, 600, M_PI / 3.);
	transform_camera(c, view);
	free(view);
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
	t_obj	*rsphere = right_obj();
	t_obj	*lsphere = left_obj();
	t_obj	*middle = middle_sphere();
	struct s_intersect		*head = add_to_world((t_obj *[]){backdrop(), f, cylinder(), lsphere, rsphere, middle}, 3);
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
	destroy_world(&world);
	destroy_canvas(&image);
	destroy_camera(&_camera);
	mlx_destroy_image(dt.mlx, dt.img);
	mlx_destroy_window(dt.mlx, dt.img);
	mlx_destroy_display(dt.mlx);
	free(dt.mlx);
	return 0;
}
