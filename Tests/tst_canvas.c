#include <criterion/criterion.h>
#include "../src/canvas/canvas.h"
#include <stdio.h>

Test(write_pixel, expected_the_pixel_with_color_red) {
	struct s_canvas *cv = canvas(10, 20);
	write_pixel(cv, 2, 3, color(1, 0, 0));
	t_color red = pixel_at(cv, 2, 3);
	cr_assert_float_eq(red[0], 1, 0.00001);
	cr_assert_float_eq(red[1], 0, 0.00001);
	cr_assert_float_eq(red[2], 0, 0.00001);
	free((void*)red);
	free(cv->img);
}

Test(write_pixel, expected_the_pixel_with_color_green) {
	struct s_canvas *cv = canvas(10, 20);
	write_pixel(cv, 2, 3, color(0, 1, 0));
	t_color green = pixel_at(cv, 2, 3);
	cr_assert_float_eq(green[0], 0, 0.00001);
	cr_assert_float_eq(green[1], 1, 0.00001);
	cr_assert_float_eq(green[2], 0, 0.00001);
	free((void*)green);
	free(cv->img);
}

Test(write_pixel, expected_the_pixel_with_color_blue) {
	struct s_canvas *cv = canvas(10, 20);
	write_pixel(cv, 2, 3, color(0, 0, 1));
	t_color blue = pixel_at(cv, 2, 3);
	cr_assert_float_eq(blue[0], 0, 0.00001);
	cr_assert_float_eq(blue[1], 0, 0.00001);
	cr_assert_float_eq(blue[2], 1, 0.00001);
	free((void*)blue);
	free(cv->img);
}

Test(write_pixel, expected_the_pixel_with_color_yellow) {
	struct s_canvas *cv = canvas(10, 20);
	write_pixel(cv, 5, 10, color(1, 1, 0));
	t_color yellow = pixel_at(cv, 5, 10);
	cr_assert_float_eq(yellow[0], 1, 0.00001);
	cr_assert_float_eq(yellow[1], 1, 0.00001);
	cr_assert_float_eq(yellow[2], 0, 0.00001);
	free((void*)yellow);
	free(cv->img);
}
