/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:06:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 19:54:26 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "canvas/canvas.h"
# include "world/world.h"
# include "camera/camera.h"

struct s_canvas	*render(t_camera *cam, struct s_world *w);
#endif
