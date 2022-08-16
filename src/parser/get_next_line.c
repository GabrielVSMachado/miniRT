/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:38:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/15 23:06:32 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include "parser.h"

static int	treat_str_read(char *src, char **dst)
{
	char	*tmp;

	tmp = NULL;
	if (*dst == NULL)
	{
		*dst = ft_strdup(src);
		if (!*dst)
			return (gnl_ERROR);
	}
	else
	{
		tmp = ft_strjoin(*dst, src);
		if (!tmp)
			return (gnl_ERROR);
		free(*dst);
		*dst = tmp;
	}
	return (NO_ERRORS);
}

static int	newline_read(char **buffer, char **line, char *p_to_newline)
{
	char	*tmp;
	int		len;

	len = p_to_newline - *buffer;
	*line = ft_substr(*buffer, 0, len);
	tmp = ft_strdup(&(*buffer)[len + 1]);
	free(*buffer);
	*buffer = tmp;
	return (gnl_READ);
}

static int	treat_error(int *fd, char **line)
{
	if (*fd < 0 || !line)
		return (gnl_ERROR);
	return (NO_ERRORS);
}

int	get_next_line(int fd, char **line)
{
	char		str_read[BUFFER_SIZE + 1];
	static char	*buffer;
	ssize_t		from_read;
	char		*p_to_newline;

	if (treat_error(&fd, line) < 0)
		return (gnl_ERROR);
	from_read = 1;
	while (from_read > 0)
	{
		from_read = read(fd, str_read, BUFFER_SIZE);
		if (from_read < 0)
			return (gnl_ERROR);
		str_read[from_read] = '\0';
		if (!treat_str_read(str_read, &buffer) && from_read != 0)
			return (gnl_ERROR);
		p_to_newline = ft_strchr(buffer, '\n');
		if (p_to_newline != NULL)
			return (newline_read(&buffer, line, p_to_newline));
	}
	*line = ft_strdup(buffer);
	free(buffer);
	buffer = NULL;
	return (gnl_EOF);
}
