#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include "../src/tuples_utils.h"
#include <math.h>

#define EPSILON 0.00001

static int	assert_float(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

Test(point, expected_a_array_with_numbers_equals_params_passed) {
	const float *tupl = point(4.3, -4.2, 3.1);
	float expected_values[] = {4.3, -4.2, 3.1, 1.0};

	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(tupl[i], expected_values[i]), 1);
	}
	free((void*)tupl);
}

Test(vector, expected_a_array_with_numbers_equals_params_passed) {
	const float *tupl = point(4.3, -4.2, 3.1);
	float expected_values[] = {4.3, -4.2, 3.1, 1.0};

	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(tupl[i], expected_values[i]), 1);
	}
	free((void*)tupl);
}

Test(add_vectors, expected_sum_of_vectors_a_and_b)	{
	const float *vector1 = vector(3, -2, 5);
	const float *vector2 = vector(-2, 3, 1);
	const float	expected_values[] = {1.0, 1.0, 6, 0};

	const float *sum = add_tuples(vector1, vector2);
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(sum[i], expected_values[i]), 1);
	}
	free((void*)vector2);
}
