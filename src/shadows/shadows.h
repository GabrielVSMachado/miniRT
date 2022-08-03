/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:57:23 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/02 23:10:16 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOWS_H
# define SHADOWS_H

# include <stdbool.h>
# include "../world/world.h"

bool	in_shadowed(struct s_world *w, t_point p);
#endif