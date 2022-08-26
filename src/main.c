/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:24:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 22:24:18 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <unistd.h>
#include <stdlib.h>
#include "linked_list.h"
#include "parser/parser.h"

static void	error_(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	main(int argc, char *argv[])
{
	struct s_global	g;

	g = (struct s_global){};
	if (argc != 2)
		error_();
	g.world = transform_values_from_file(argv[1], &g.cam);
	if (!g.world)
		error_();
	render(&g);
	return (0);
}
