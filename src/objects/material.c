/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:55:33 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/07/30 17:48:41 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <stdlib.h>

struct s_material	*material(void)
{
	struct s_material	*m;

	m = malloc(sizeof(struct s_material));
	if (!m)
		return (NULL);
	m->ambient = 0.1;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200.0;
	m->c = color(1, 1, 1);
	return (m);
}

void	destroy_material(struct s_material **m)
{
	free((*m)->c);
	free(*m);
	*m = NULL;
}
