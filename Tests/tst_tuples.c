#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include "../src/vectors/vectors.h"
#include <math.h>

#define EPSILON 0.00001

static int	assert_float(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

Test(point, expected_a_array_with_numbers_equals_params_passed) {
	const double *tupl = point(4.3, -4.2, 3.1);
	double expected_values[] = {4.3, -4.2, 3.1, 1.0};

	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(tupl[i], expected_values[i]), 1);
	}
	free((void*)tupl);
}

Test(vector, expected_a_array_with_numbers_equals_params_passed) {
	double *tupl = point(4.3, -4.2, 3.1);
	double expected_values[] = {4.3, -4.2, 3.1, 1.0};

	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(tupl[i], expected_values[i]), 1);
	}
	free((void*)tupl);
}

Test(add_vectors, expected_sum_of_vectors_a_and_b)	{
	double *vector1 = vector(3, -2, 5);
	double *vector2 = vector(-2, 3, 1);
	double	expected_values[] = {1.0, 1.0, 6, 0};

	double *sum = add_tuples(vector1, vector2);
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(sum[i], expected_values[i]), 1);
	}
	free((void*)vector2);
}

Test(sub_vectors, expected_sub_of_vectors_a_and_b)
{
	double *v1 = vector(3, 2, 1);
	double *v2 = vector(5, 6, 7);
	double expected_values[] = {-2, -4, -6, 0};

	double *sub = sub_tuple(v1, v2);
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(sub[i],expected_values[i]), 1);
	}
	free((void*)v1);
	free((void*)v2);
	free((void*)sub);
}

Test(sub_points, expected_vector) {
	double *p1 = point(3, 2, 1);
	double *p2 = point(5, 6, 7);
	double expected_values[] = {-2, -4, -6, 0};

	double *v1 = sub_tuple(p1, p2);
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(v1[i],expected_values[i]), 1);
	}
	free((void*)p1);
	free((void*)p2);
	free((void*)v1);
}

Test(sub_vector_from_point, expected_sub_of_vectors_a_and_b)
{
	double *p1 = point(3, 2, 1);
	double *v2 = vector(5, 6, 7);
	double expected_values[] = {-2, -4, -6, 1};

	double *sub = sub_tuple(p1, v2);
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(sub[i],expected_values[i]), 1);
	}
	free((void*)p1);
	free((void*)v2);
	free((void*)sub);
}

Test(negate_vectors, expected_oposite_vector) {
	double *v = vector(3, 2, 1);
	double *nv = negate_tuple(v);
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(nv[i], 0 - v[i]), 1);
	}
	free((void*)nv);
	free((void*)v);
}

Test(scalar_multiplication, one_vector_by_2) {
	double *t1 = vector(2, 1, 4);
	double *result = scalar_multiplication(t1, 2);
	double expected_values[] = {4, 2, 8, 0};
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(result[i], expected_values[i]), 1);
	}
	free((void *)t1);
	free((void *)result);
}

Test(scalar_multiplication, one_vector_by_half) {
	double *t1 = vector(2, 1, 4);
	double *result = scalar_multiplication(t1, 0.5);
	double expected_values[] = {1, 0.5, 2.0, 0};
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(result[i], expected_values[i]), 1);
	}
	free((void *)t1);
	free((void *)result);
}

Test(magnitude, expected_values_magnitude_1) {
	double *v = vector(1, 0, 0);
	double result = magnitude(v);
	cr_assert_eq(assert_float(result, 1), 1);
	free((void*)v);
}

Test(magnitude, expected_value_magnitude_sqrt_of_14) {
	double *v = vector(1, 2, 3);
	double result = magnitude(v);
	double expected_value = sqrtf(14);
	cr_assert_eq(assert_float(result, expected_value), 1);
	free((void*)v);
}

Test(normalize, expected_vector_normalized)
{
	t_vector v = vector(4, 0, 0);
	t_vector nv = normalize(v);
	t_vector	expected_value = vector(1, 0, 0);

	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(nv[i], expected_value[i]), 1);
	}
	free((void*)v);
	free((void*)nv);
	free((void*)expected_value);
}

Test(normalize, expected_vector_normalized_2)
{
	t_vector v = vector(1, 2, 3);
	t_vector nv = normalize(v);
	double	expected_value[] = {1.0, 2.0, 3.0, 0};
	double	mag_expcted_value = sqrtf(14);
	for (int i = 0; i < 4; i++) {
		expected_value[i] *= (1 / mag_expcted_value);
	}
	for (int i = 0; i < 4; i++) {
		cr_assert_eq(assert_float(nv[i], expected_value[i]), 1);
	}
	free((void*)v);
	free((void*)nv);
}

Test(dot_product, expected_0) {
	t_vector v1 = vector(2, 0, 0);
	t_vector v2 = vector(0, 2, 0);
	double result = dot_product(v1, v2);
	cr_assert_eq(result, 0);
	free((void*)v1);
	free((void*)v2);
}

Test(dot_product, expected_12) {
	t_vector v1 = vector(2, 2, 2);
	t_vector v2 = vector(2, 2, 2);
	double result = dot_product(v1, v2);
	cr_assert_eq(result, 12);
	free((void*)v1);
	free((void*)v2);
}

Test(cross_product, expected_vector_z) {
	t_vector v1 = vector(1, 2, 3);
	t_vector v2 = vector(2, 3.0, 4);
	t_vector z = vector(-1, 2, -1);
	t_vector result = cross_product(v1, v2);

	for (int i = 0; i < 3; i++) {
		cr_assert_eq(assert_float(z[i], result[i]), 1);
	}
	free((void*)v1);
	free((void*)v2);
	free((void*)z);
	free((void*)result);
}

Test(cross_product, expected_vector_f) {
	t_vector v1 = vector(1, 2, 3);
	t_vector v2 = vector(2, 3.0, 4);
	t_vector f = vector(1, -2, 1);
	t_vector result = cross_product(v2, v1);

	for (int i = 0; i < 3; i++) {
		cr_assert_eq(assert_float(f[i], result[i]), 1);
	}
	free((void*)v1);
	free((void*)v2);
	free((void*)f);
	free((void*)result);
}
