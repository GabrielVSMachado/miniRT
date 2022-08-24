/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:47:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/23 23:38:43 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_parser.h"
#include <stdbool.h>
#include <math.h>
#include "ft_string.h"
#include "../vectors/vectors.h"

#define EPISLON 0.00001

bool	check_normalized_vector(char *value)
{
	char		**splited;
	t_vector	nv;
	bool		result;

	splited = ft_split(value, ',');
	if (!splited)
		return (NULL);
	nv = vector(ft_atod(splited[0]), ft_atod(splited[1]), ft_atod(splited[2]));
	result = fabs(magnitude(nv) - 1) < EPISLON;
	free(nv);
	destroy_content(splited);
	return (result);
}

bool	validate_colors(char *color)
{
	int		rgb;
	int		i;
	char	**values;

	i = -1;
	values = ft_split(color, ',');
	while (values[++i])
	{
		rgb = ft_atoi(values[i]);
		if (rgb < 0 || rgb > 255)
		{
			destroy_content(values);
			return (false);
		}
	}
	destroy_content(values);
	return (true);
}

bool	validate_double_between_range(char *value, double max, double min)
{
	char	**splited_value;
	double	value_type_numeric;
	int		i;

	splited_value = ft_split(value, ',');
	i = -1;
	while (splited_value[++i])
	{
		value_type_numeric = ft_atod(splited_value[i]);
		if (value_type_numeric < min || value_type_numeric > max)
		{
			destroy_content(splited_value);
			return (false);
		}
	}
	destroy_content(splited_value);
	return (true);
}

bool	validate_number_of_pointers(char **line_values, int expected_number)
{
	int	actual_number;

	actual_number = -1;
	while (line_values[++actual_number])
		;
	return (actual_number == expected_number);
}
