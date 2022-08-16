/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:02:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/16 00:59:02 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include <stdbool.h>
#include "ft_string.h"
#include "ft_ctype.h"

void	destroy_content(void *content)
{
	char	**tmp;

	if (!content)
		return ;
	tmp = (char **)content;
	while (*tmp)
	{
		free(*tmp);
		++(*tmp);
	}
	free(content);
}

static bool	is_valid_word(const char *word)
{
	if (!ft_isalpha(*word) || (word[1] != '\0' && word[2] != '\0'))
		return (false);
	return (
		(word[0] == 'A' && word[1] == '\0')
		|| (word[0] == 'C' && word[1] == '\0')
		|| (word[0] == 'L' && word[1] == '\0')
		|| !ft_strncmp(word, "sp", 2)
		|| !ft_strncmp(word, "pl", 2)
		|| !ft_strncmp(word, "cy", 2)
	);
}

static bool	is_valid_number(char *word)
{
	while (*word)
	{
		if (*word != '-' && !ft_isdigit(*word) && *word != ',' && *word != '.')
			return (false);
		++word;
	}
	return (true);
}

bool	is_valid_line(char *line_striped[])
{
	int	i;

	i = 0;
	if (!is_valid_word(line_striped[0]))
		return (false);
	while (line_striped[++i])
	{
		if (!is_valid_number(line_striped[i]))
			return (false);
	}
	return (true);
}
