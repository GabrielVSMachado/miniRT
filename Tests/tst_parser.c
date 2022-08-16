#include <criterion/criterion.h>
#include "../src/parser/parser.h"

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