/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/22 20:00:06 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HSIZE 800
# define VSIZE 800

# include "canvas/canvas.h"
# include "world/world.h"
# include "camera/camera.h"

struct s_canvas	*render(t_camera *cam, struct s_world *w);
#endif
