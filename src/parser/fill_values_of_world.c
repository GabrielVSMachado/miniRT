/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_values_of_world.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:37:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/08/23 23:39:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_parser.h"
#include "../camera/camera.h"
#include "../phong_reflection_model/lights.h"
#include "../intersections/intersections.h"

static t_list	*get_environment_light_line(t_list *lines)
{
	char	**tmp;

	while (lines)
	{
		tmp = lines->content;
		if (tmp[0][0] == 'A')
			return (lines);
		lines = lines->next;
	}
}

static void	fill_values_for_environment_light(
	t_color *envc, double *intensity, t_list *lines)
{
	char	**content;

	content = (char **)(get_environment_light_line(lines)->content);
	*envc = get_color(content[2]);
	*intensity = ft_atod(content[1]);
}

static struct s_intersect	*iterate_through_lines(
	t_list *head, t_light **light, t_camera **cam)
{
	double				intensity_env;
	char				**content;
	t_color				envc;
	struct s_intersect	*objects;

	fill_values_for_environment_light(&envc, &intensity_env, head);
	objects = NULL;
	while (head)
	{
		content = (char **)head->content;
		if (content[0][0] == 'C')
			*cam = get_values_camera(content);
		else if (content[0][0] == 'L')
			*light = get_values_light(content);
		else if (content[0][0] == 's' && content[0][1] == 'p')
			add_back(&objects, get_values_sphere(content, envc, intensity_env));
		else if (content[0][0] == 'p' && content[0][1] == 'l')
			add_back(&objects, get_values_plane(content, envc, intensity_env));
		else if (content[0][0] == 'c' && content[0][1] == 'y')
			add_back(
				&objects, get_values_cylinder(content, envc, intensity_env));
		head = head->next;
	}
	free(envc);
	return (head);
}

struct s_world	*transform_values_from_file(const char *path, t_camera **cam)
{
	t_list				*lines_file;
	struct s_intersect	*head;
	t_light				*light;

	lines_file = get_values_from_file(path);
	if (!lines_file)
		return (NULL);
	head = iterate_through_lines(lines_file, &light, cam);
	ft_lstclear(&lines_file, destroy_content);
	return (init_world(light, head));
}
