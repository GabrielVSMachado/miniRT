/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:05:20 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/16 00:23:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include "linked_list.h"
# include <stdbool.h>
# define NO_ERRORS 1

enum e_returns
{
	gnl_ERROR = -1,
	gnl_EOF = 0,
	gnl_READ = 1,
};

int		get_next_line(int fd, char **line);
void	destroy_content(void *node);
bool	is_valid_line(char *line_striped[]);
t_list	*get_lines_from_file(const char *path);
#endif
