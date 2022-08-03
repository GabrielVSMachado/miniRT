#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
# include "../src/camera/camera.h"
#include "utils.h"

static t_point from, to;
static t_vector up;
static t_matrix *result, *expected;

void fini_view(void)
{
	free(result);
	free(expected);
	free(from);
	free(to);
	free(up);
	result = NULL;
	expected = NULL;
	from = NULL;
	to = NULL;
	up = NULL;
}
	
Test(view_transformation,
		the_transformation_matrix_for_the_default_orientation, .fini=fini_view)
{
	from = point(0, 0, 0);
	to = point(0, 0, -1);
	up = vector(0, 1, 0);
	result = view_transformation(from, to, up);
	expected = identity();
	cr_assert(assert_matrices(result->mtx, expected->mtx, expected->shape) == true);
}

Test(view_transformation,
		A_view_transformation_matrix_looking_in_positive_z_direction,
		.fini=fini_view)
{
	from = point(0, 0, 0);
	to = point(0, 0, 1);
	up = vector(0, 1, 0);
	result = view_transformation(from, to, up);
	expected = scale(-1, 1, -1);
	cr_assert(assert_matrices(result->mtx, expected->mtx, expected->shape) == true);
}

Test(view_transformation,
		the_view_transformation_moves_the_world, .fini=fini_view)
{
	from = point(0, 0, 8);
	to = point(0, 0, 0);
	up = vector(0, 1, 0);
	result = view_transformation(from, to, up);
	expected = translate(0, 0, -8);
	cr_assert(assert_matrices(result->mtx, expected->mtx, expected->shape) == true);
}

Test(view_transformation,
		An_arbitrary_view_transformation, .fini=fini_view)
{
	from = point(1, 3, 2);
	to = point(4, -2, 8);
	up = vector(1, 1, 0);
	result = view_transformation(from, to, up);
	expected = matrix((double [][4]){
			{-0.50709, 0.50709, 0.67612, -2.36643},
			{0.76772, 0.60609, 0.12122, -2.82843},
			{-0.35857, 0.59761, -0.71714, 0.0},
			{0, 0, 0, 1}
			}, (unsigned int []){4, 4});
	cr_assert(assert_matrices(result->mtx, expected->mtx, expected->shape) == true);
}
