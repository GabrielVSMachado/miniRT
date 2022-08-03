#include <criterion/criterion.h>
#include "../src/canvas/canvas.h"

Test(colors, expected_tuple_with_values_of_colors) {
	t_color	cr = color(-0.1, 0.4, 0.7);
	cr_assert_float_eq(cr[0], -0.1, 0.0001);
	cr_assert_float_eq(cr[1], 0.4, 0.0001);
	cr_assert_float_eq(cr[2], 0.7, 0.0001);
	free((void*)cr);
}

Test(add_colors, expected_tuple_with_sum_of_colors) {
	t_color c1 = color(0.9, 0.6, 0.75);
	t_color c2 = color(0.7, 0.1, 0.25);
	t_color result = add_colors(c1, c2);
	cr_assert_float_eq(result[0], 1.6, 0.0001);
	cr_assert_float_eq(result[1], 0.7, 0.0001);
	cr_assert_float_eq(result[2], 1.0, 0.0001);
	free((void*)c1);
	free((void*)c2);
	free((void*)result);
}

Test(handamard_product, expected_color_with_which_value_eq_product_of_c1_and_c2)
{
	t_color c1 = color(1, 0.2, 0.4);
	t_color c2 = color(0.9, 1, 0.1);
	t_color result = colors_product(c1, c2);
	cr_assert_float_eq(result[0], 0.9, 0.0001);
	cr_assert_float_eq(result[1], 0.2, 0.0001);
	cr_assert_float_eq(result[2], 0.04, 0.0001);
	free((void*)c1);
	free((void*)c2);
	free((void*)result);
}
