/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rt_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:03:49 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/16 00:58:50 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "parser.h"
#include "ft_string.h"

static void	clear_on_error(t_list **head, char **splited_line, int fd)
{
	ft_lstclear(head, destroy_content);
	destroy_content(splited_line);
	close(fd);
}

t_list	*get_lines_from_file(const char *path)
{
	t_list	*head;
	char	*line;
	int		fd;
	int		gnl_return;
	char	**splited_line;

	head = NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (true)
	{
		gnl_return = get_next_line(fd, &line);
		if (gnl_return == 0)
			break ;
		if (gnl_return <= 0)
			return (free(line), clear_on_error(&head, splited_line, fd), NULL);
		splited_line = ft_split(line, ' ');
		free(line);
		if (!splited_line || !is_valid_line(splited_line))
			return (clear_on_error(&head, splited_line, fd), NULL);
		ft_lstadd_back(&head, ft_lstnew(splited_line));
	}
	return (head);
}
