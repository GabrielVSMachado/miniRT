/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rt_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:03:49 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/20 21:45:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "utils_parser.h"
#include "ft_string.h"
#include <stdlib.h>

static void	clear_on_error(t_list **head, char **splited_line, int fd)
{
	ft_lstclear(head, destroy_content);
	destroy_content(splited_line);
	close(fd);
}

static t_list	*get_lines_from_file(int fd)
{
	t_list	*head;
	char	*line;
	int		gnl_return;
	char	**splited_line;

	head = NULL;
	if (fd < 0)
		return (NULL);
	while (gnl_return)
	{
		gnl_return = get_next_line(fd, &line);
		if (gnl_return < 0)
			return (clear_on_error(&head, splited_line, fd), NULL);
		if (!*line)
		{
			free(line);
			continue ;
		}
		splited_line = ft_split(line, ' ');
		if (free(line), !splited_line || !is_valid_line(splited_line))
			return (clear_on_error(&head, splited_line, fd), NULL);
		ft_lstadd_back(&head, ft_lstnew(splited_line));
	}
	return (head);
}

t_list	*get_values_from_file(const char *path)
{
	t_list	*head;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	head = get_lines_from_file(fd);
	if (!head)
		return (NULL);
	if (!validate_inputs(head))
	{
		ft_lstclear(&head, destroy_content);
		return (NULL);
	}
	return (head);
}
