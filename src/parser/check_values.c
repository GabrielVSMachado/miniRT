/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 14:01:59 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/22 19:35:31 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_parser.h"
#include <stdbool.h>

bool	check_values_for_camera(char **line)
{
	if (!validate_number_of_pointers(line, 4))
		return (false);
	else if (!validate_double_between_range(line[2], 1, -1))
		return (false);
	else if (!check_normalized_vector(line[2]))
		return (false);
	return (validate_double_between_range(line[3], 180, 0));
}

bool	check_values_for_light(char **line)
{
	if (!validate_number_of_pointers(line, 4))
		return (false);
	return (validate_double_between_range(line[2], 1, 0));
}

bool	check_values_for_sphere(char **line)
{
	if (!validate_number_of_pointers(line, 4))
		return (false);
	return (validate_colors(line[3]));
}

bool	check_values_for_plane(char **line)
{
	if (!validate_number_of_pointers(line, 4))
		return (false);
	else if (!validate_double_between_range(line[2], 1, -1))
		return (false);
	else if (!check_normalized_vector(line[2]))
		return (false);
	return (validate_colors(line[3]));
}

bool	check_values_for_cylinder(char **line)
{
	if (!validate_number_of_pointers(line, 6))
		return (false);
	else if (!validate_double_between_range(line[2], 1, -1))
		return (false);
	else if (!check_normalized_vector(line[2]))
		return (false);
	return (validate_colors(line[5]));
}
