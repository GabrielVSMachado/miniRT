/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:02:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/20 21:26:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include <stdbool.h>
#include "ft_string.h"
#include "ft_ctype.h"

void	destroy_content(void *content)
{
	char	**tmp;
	int		_;

	if (!content)
		return ;
	tmp = content;
	_ = -1;
	while (tmp[++_])
		free(tmp[_]);
	free((char **)content);
}

static bool	is_valid_word(const char *word)
{
	if (!ft_isalpha(*word) || (word[1] != '\0' && word[2] != '\0'))
		return (false);
	return (
		(word[0] == 'A' && word[1] == '\0')
		|| (word[0] == 'C' && word[1] == '\0')
		|| (word[0] == 'L' && word[1] == '\0')
		|| !ft_strcmp(word, "sp")
		|| !ft_strcmp(word, "pl")
		|| !ft_strcmp(word, "cy")
	);
}

static bool	is_valid_number(char *word)
{
	while (*word)
	{
		if (*word != '-'
			&& !ft_isdigit(*word)
			&& *word != ','
			&& *word != '.'
			&& *word != ' ')
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
