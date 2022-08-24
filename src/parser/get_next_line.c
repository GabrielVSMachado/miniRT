/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:38:18 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/23 23:29:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_parser.h"
#include "ft_string.h"
#include <unistd.h>
#include <stdlib.h>

static int	newline_read(char **buffer, char **line, char *p_to_newline);
static int	treat_str_read(char *src, char **dst);

int	get_next_line(int fd, char **line)
{
	char		str_read[BUFFER_SIZE + 1];
	static char	*buffer[FD_SETSIZE];
	ssize_t		from_read;
	char		*p_to_newline;

	if (fd < 0)
		return (-1);
	from_read = 1;
	while (from_read > 0)
	{
		from_read = read(fd, str_read, BUFFER_SIZE);
		if (from_read < 0)
			return (-1);
		str_read[from_read] = '\0';
		if (!treat_str_read(str_read, &buffer[fd]) && from_read != 0)
			return (-1);
		p_to_newline = ft_strchr(buffer[fd], '\n');
		if (p_to_newline != NULL)
			return (newline_read(&buffer[fd], line, p_to_newline));
	}
	*line = ft_strdup(buffer[fd]);
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (0);
}

static int	treat_str_read(char *src, char **dst)
{
	char	*tmp;

	tmp = NULL;
	if (*dst == NULL)
	{
		*dst = ft_strdup(src);
		return (2 * (!*dst) - 1);
	}
	tmp = ft_strjoin(*dst, src);
	if (!tmp)
		return (-1);
	free(*dst);
	*dst = tmp;
	return (1);
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
	return (1);
}
