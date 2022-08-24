/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inputs_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 00:29:42 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/20 21:54:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_parser.h"
#include <linked_list.h>
#include "ft_string.h"

static bool	check_values_for_ambient_light(char **line)
{
	if (!validate_number_of_pointers(line, 3))
		return (false);
	return (validate_colors(line[2]));
}

bool	validate_inputs(t_list *readed_lines)
{
	char	**content;
	bool	result;
	int		quanti_acl[3];

	ft_bzero(quanti_acl, sizeof(int) * 3);
	while (readed_lines)
	{
		content = (char **)readed_lines->content;
		if (*content[0] == 'A' && ++quanti_acl[0])
			result = check_values_for_ambient_light(content);
		else if (*content[0] == 'C' && ++quanti_acl[1])
			result = check_values_for_camera(content);
		else if (*content[0] == 'L' && ++quanti_acl[2])
			result = check_values_for_light(content);
		else if (content[0][0] == 's' && content[0][1] == 'p')
			result = check_values_for_sphere(content);
		else if (content[0][0] == 'c' && content[0][1] == 'y')
			result = check_values_for_cylinder(content);
		else
			result = check_values_for_plane(content);
		if (!result)
			return (false);
		readed_lines = readed_lines->next;
	}
	return (quanti_acl[0] == 1 && quanti_acl[1] == 1 && quanti_acl[2] == 1);
}
