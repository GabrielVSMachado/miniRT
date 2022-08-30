/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rt_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:03:49 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/25 22:30:20 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "utils_parser.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

static void	*clear_on_error(t_list **head, char **splited_line)
{
	ft_lstclear(head, destroy_content);
	destroy_content(splited_line);
	return (NULL);
}

static void	switch_tokens(char **line)
{
	int		i;
	bool	coma_founded;

	coma_founded = false;
	i = -1;
	while ((*line)[++i])
	{
		while (coma_founded && (*line)[i] == ' ')
		{
			(*line)[i] = -1;
			++i;
		}
		coma_founded = (*line)[i] == ',';
	}
}

static void	switch_back(char **splited_line)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (splited_line[++i])
	{
		j = -1;
		while (splited_line[i][++j])
		{
			tmp = splited_line[i][j];
			splited_line[i][j] = ' ' * (tmp == -1) + tmp * (tmp != -1);
		}
	}
}

static t_list	*get_lines_from_file(int fd)
{
	t_list	*head;
	char	*line;
	int		gnl_return;
	char	**splited_line;

	head = NULL;
	gnl_return = 1;
	line = NULL;
	while (gnl_return)
	{
		free(line);
		gnl_return = get_next_line(fd, &line);
		if (gnl_return < 0)
			return (clear_on_error(&head, NULL));
		if (!*line)
			continue ;
		switch_tokens(&line);
		splited_line = ft_split(line, ' ');
		switch_back(splited_line);
		if (!splited_line || !is_valid_line(splited_line))
			return (clear_on_error(&head, splited_line));
		ft_lstadd_back(&head, ft_lstnew(splited_line));
	}
	free(line);
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
	close(fd);
	if (!head)
		return (NULL);
	if (!validate_inputs(head))
	{
		ft_lstclear(&head, destroy_content);
		return (NULL);
	}
	return (head);
}
