/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:18:36 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/23 23:29:20 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_PARSER_H
# define UTILS_PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include "linked_list.h"
# include <stdbool.h>
# include "../canvas/canvas.h"
# include "../camera/camera.h"
# include "../phong_reflection_model/lights.h"

# define TOKEN -1

t_color				get_color(char *_color);
t_list				*get_values_from_file(const char *path);
t_list				*validate_lines(const char *path);
t_vector			get_vector(char *vector_);
int					get_next_line(int fd, char **line);
bool				is_valid_line(char *line_striped[]);
void				destroy_content(void *content);
bool				validate_inputs(t_list *readed_lines);
bool				validate_colors(char *color);
bool				validate_double_between_range(
						char *value, double max, double min);
bool				validate_number_of_pointers(
						char **line_values, int expected_number);
bool				check_values_for_cylinder(char **line);
bool				check_values_for_plane(char **line);
bool				check_values_for_sphere(char **line);
bool				check_values_for_light(char **line);
bool				check_values_for_camera(char **line);
bool				check_normalized_vector(char *value);
t_camera			*get_values_camera(char **content);
t_light				*get_values_light(char **content);
struct s_intersect	*get_values_cylinder(
						char **content, t_color	envc, double intensity_env);
struct s_intersect	*get_values_plane(
						char **content, t_color envc, double intensity_env);
struct s_intersect	*get_values_sphere(
						char **content, t_color envc, double intensity_env);
#endif
