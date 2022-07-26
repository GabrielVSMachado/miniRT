/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:56:10 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/02 20:57:09 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "utils_colors.h"

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
#endif
