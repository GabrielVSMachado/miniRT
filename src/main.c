/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:37:11 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/25 09:52:57 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples_utils.h"
#include "utils_canvas.h"
#include "utils_colors.h"
#include <math.h>
#include <stdio.h>

#define WIDTH 450
#define HEIGHT 275

typedef struct s_prj
{
	t_vector	velocity;
	t_point		position;
}	t_prj;

struct s_env
{
	t_vector	g;
	t_vector	wind;
};

void	tick(struct s_env *e, t_prj *prj)
{
	prj->position = add_tuples(prj->position, prj->velocity);
	prj->velocity = add_tuples(prj->velocity, e->g);
	prj->velocity = add_tuples(prj->velocity, e->wind);
}

void	print_on_ascii(struct s_canvas *cv)
{
	for (int i = HEIGHT; i > 0; --i) {
		for (int j = WIDTH; j > 0.; --j) {
			if (cv->img[i + j] == 0x00ff0000) {
				printf("\033[33m0\033[39m");
			} else {
				printf("#");
			}
		}
		printf("\n");
	}
}

int	main(void)
{
	struct s_canvas	*cv;
	struct s_env	e;
	t_prj			prj;

	prj.position = point(0, 1, 0);
	prj.velocity = scalar_multiplication(normalize(vector(1, 1.8, 0)), 1.25);
	e.g = vector(0, -0.1, 0);
	e.wind = vector(-0.01, 0, 0);
	t_color	c = color(1, 0, 0);

	float px, py;

	cv = canvas(WIDTH, HEIGHT);

	while (prj.position[1] > 0.99)
	{
		py = (HEIGHT - 1) - (prj.position[1] * HEIGHT/10.);
		px = prj.position[0] * (WIDTH/10.);
		write_pixel(cv, px, py, c);
		tick(&e, &prj);
	}
	print_on_ascii(cv);
	return (0);
}
