/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 22:22:47 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGHT 1000
# define WIDTH 1000

# include "canvas/canvas.h"
# include "world/world.h"
# include "camera/camera.h"
# include "mlx_functions/utils_mlx.h"

struct s_global
{
	struct s_world	*world;
	t_camera		*cam;
	struct s_data	data;
	struct s_canvas	*final_img;
};

void	render(struct s_global *g);
void	error(struct s_global *g);
void	destroy_global(struct s_global *g);
#endif
