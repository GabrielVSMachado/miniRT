#include <criterion/criterion.h>
#include "../src/parser/parser.h"
#include <stdbool.h>
#include "ft_string.h"
#include "../src/camera/camera.h"
#include <string.h>
#include "../src/parser/utils_parser.h"
#include <fcntl.h>
#include "utils.h"
#include <math.h>

static void	clear_on_error(t_list **head, char **splited_line, int fd)
{
	ft_lstclear(head, destroy_content);
	destroy_content(splited_line);
	close(fd);
}


static t_list	*get_lines_from_file(const char *path)
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

Test(parser, wrong_letter_in_start_of_line)
{
	t_list	*head = get_lines_from_file("./test_1.rt");
	cr_assert_null(head);
}

Test(parser, missconfig_with_tabs)
{
	t_list	*head = get_lines_from_file("./test_2.rt");
	cr_assert_null(head);
}

Test(parser, missconfig_slash_between_numbers)
{
	t_list	*head = get_lines_from_file("./test_3.rt");
	cr_assert_null(head);
}

Test(validate_colors, expected_color_pointer_untouched)
{
	char	*color = strdup("255,255,255");
	cr_assert_eq(validate_colors(color), true);
	cr_assert_str_eq(color, "255,255,255");
}

Test(validate_colors, expected_false)
{
	char	*color = strdup("255,256,255");
	cr_assert_eq(validate_colors(color), false);
	cr_assert_str_eq(color, "255,256,255");
}

Test(validate_colors, expected_false_2)
{
	char	*color = strdup("255,-1,255");
	cr_assert_eq(validate_colors(color), false);
	cr_assert_str_eq(color, "255,-1,255");
}

Test(validate_double_between_range, check_one_number_and_expected_true)
{
	char	*value = strdup("0.765");
	cr_assert_eq(validate_double_between_range(value, 1, -1), true);
	cr_assert_str_eq(value, "0.765");
}

Test(validate_double_between_range, check_one_number_and_expected_false)
{
	char	*value = strdup("0.765");
	cr_assert_eq(validate_double_between_range(value, 0.764, -1), false);
	cr_assert_str_eq(value, "0.765");
}

Test(validate_double_between_range, check_one_number_and_expected_false_2)
{
	char	*value = strdup("0.7652341");
	cr_assert_eq(validate_double_between_range(value, 0.7652340, -1), false);
	cr_assert_str_eq(value, "0.7652341");
}

Test(validate_double_between_range, check_one_number_and_expected_false_3)
{
	char	*value = strdup("-0.7652341");
	cr_assert_eq(validate_double_between_range(value, 1, -0.7652340), false);
	cr_assert_str_eq(value, "-0.7652341");
}

Test(validate_double_between_range, check_three_numbers_splited_by_coma_expected_true)
{
	char	*value = strdup("1.2,4.5,6.0");
	cr_assert_eq(validate_double_between_range(value, 6.1, 1.1), true);
	cr_assert_str_eq(value, "1.2,4.5,6.0");
}

Test(get_values_camera, check_up_values)
{
	char	*content[] = {"C", "0,1.5,-5", "0,1,0", "60", NULL};
	t_camera	*cam = get_values_camera(content);
	t_camera	*cam_expected = camera(0, 0, M_PI / 3.);
	transform_camera(cam, view_transformation(
		point(0, 1.5, -5),
		point(0, 1, 0),
		vector(0, 1, 0)
	));
	assert_matrices(cam->tranform->mtx, cam_expected->tranform->mtx, cam_expected->tranform->shape);
}