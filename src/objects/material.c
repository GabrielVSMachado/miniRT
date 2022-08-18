/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:55:33 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/17 22:59:16 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>

struct s_material	*material(
	t_color obj_color, t_color env_color, double ambient)
{
	struct s_material	*m;

	m = malloc(sizeof(struct s_material));
	if (!m)
		return (NULL);
	m->ambient = ambient;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200.0;
	m->objc = obj_color;
	m->envc = env_color;
	return (m);
}

void	destroy_material(struct s_material **m)
{
	free((*m)->objc);
	free((*m)->envc);
	free(*m);
	*m = NULL;
}
