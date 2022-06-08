#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <math.h>
#include <stdbool.h>
#include "../src/matrix.h"

Test(translation, expected_a_point) {
	t_matrix	*trans = translation(5, -3, 2);
	t_matrix	*m = matrix((t_tuple []){
			tuple(-3, 0, 0, 0),
			tuple(4, 0, 0, 0),
			tuple(5, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrixs_product(trans, m);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(2, 0, 0, 0),
			tuple(1, 0, 0, 0),
			tuple(7, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&trans);
	destroy_matrix(&m);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(translation, expected_a_point2) {
	t_matrix	*trans = translation(5, -3, 2);
	t_matrix	*itrans = inverse(trans);
	t_matrix	*p = matrix((t_tuple []){
			tuple(-3, 0, 0, 0),
			tuple(4, 0, 0, 0),
			tuple(5, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrixs_product(itrans, p);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(-8, 0, 0, 0),
			tuple(7, 0, 0, 0),
			tuple(3, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&trans);
	destroy_matrix(&itrans);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(translation, expected_value_eq_vector) {
	t_matrix	*v = matrix((t_tuple []){
			tuple(-3, 0, 0, 0),
			tuple(4, 0, 0, 0),
			tuple(5, 0, 0, 0),
			tuple(0, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*trans = translation(5, -3, 2);
	t_matrix	*result = matrixs_product(trans, v);
	cr_assert(assert_t_matrix_eq(result, v) == true);
	destroy_matrix(&v);
	destroy_matrix(&trans);
	destroy_matrix(&result);
}

Test(scaling, expected_the_point_scaled_by_the_matrix_A) {
	t_matrix *A = scalating(2, 3, 4);
	t_matrix *p = matrix((t_tuple []){
			tuple(-4, 0, 0, 0),
			tuple(6, 0, 0, 0),
			tuple(8, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrixs_product(A, p);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(-8, 0, 0, 0),
			tuple(18, 0, 0, 0),
			tuple(32, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&A);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(scaling, expected_the_vector_scaled_by_the_matrix_A) {
	t_matrix *A = scalating(2, 3, 4);
	t_matrix *p = matrix((t_tuple []){
			tuple(-4, 0, 0, 0),
			tuple(6, 0, 0, 0),
			tuple(8, 0, 0, 0),
			tuple(0, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrixs_product(A, p);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(-8, 0, 0, 0),
			tuple(18, 0, 0, 0),
			tuple(32, 0, 0, 0),
			tuple(0, 0, 0, 0)
			}, (unsigned int []){4, 1});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&A);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(scaling, expected_the_point_shrink_by_the_matrix_A)
{
	t_matrix *A = inverse(scalating(2, 3, 4));
	t_matrix *p = matrix((t_tuple []){
			tuple(-4, 0, 0, 0),
			tuple(6, 0, 0, 0),
			tuple(8, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrixs_product(A, p);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(-2, 0, 0, 0),
			tuple(2, 0, 0, 0),
			tuple(2, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&A);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(scaling, try_reflect_a_point_in_x_axis) {
	t_matrix	*scl = scalating(-1, 1, 1);
	t_matrix	*p = matrix((t_tuple []){
			tuple(2, 0, 0, 0),
			tuple(3, 0, 0, 0),
			tuple(4, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrixs_product(scl, p);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(-2, 0, 0, 0),
			tuple(3, 0, 0, 0),
			tuple(4, 0, 0, 0),
			tuple(1, 0, 0, 0)
			}, (unsigned int []){4, 1});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&scl);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
	destroy_matrix(&p);
}

Test(rotation_axis_x, expected_point_after_rotation_in_half_way_to_axis_z) {
	t_matrix	*rt = rotation_x(M_PI_4);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrixs_product(rt, p);
	t_matrix	*expected_value = mpoint(0, M_SQRT2/2,  M_SQRT2/2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&result);
	destroy_matrix(&rt);
	destroy_matrix(&p);
	destroy_matrix(&expected_value);
}

Test(rotation_axis_x, expected_point_after_rotation_in_axis_z)
{
	t_matrix	*rt = rotation_x(M_PI_2);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrixs_product(rt, p);
	t_matrix	*expected_value = mpoint(0, 0, 1);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&result);
	destroy_matrix(&rt);
	destroy_matrix(&p);
	destroy_matrix(&expected_value);

}

Test(rotation_axis_x, expected_point_after_rotation_in_axis_x)
{
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*rt = rotation_x(M_PI_4);
	t_matrix	*irt = inverse(rt);
	t_matrix	*result = matrixs_product(irt, p);
	t_matrix	*expected_value = mpoint(0, M_SQRT2/2, -M_SQRT2/2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&p);
	destroy_matrix(&rt);
	destroy_matrix(&irt);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(rotation_axis_y, rotating_a_point_a_positive_half_quarter_of_y_axis)
{
	t_matrix	*rt = rotation_y(M_PI_4);
	t_matrix	*p = mpoint(0, 0, 1);
	t_matrix	*result = matrixs_product(rt, p);
	t_matrix	*expected_value = mpoint(M_SQRT2/2, 0, M_SQRT2/2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&p);
	destroy_matrix(&rt);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(rotation_axis_y, rotating_a_point_a_negative_half_quarter_of_y_axis){
	t_matrix	*rt = rotation_y(M_PI_4);
	t_matrix	*irt = inverse(rt);
	t_matrix	*p = mpoint(0, 0, 1);
	t_matrix	*result = matrixs_product(irt, p);
	t_matrix	*expected_value = mpoint(-M_SQRT2/2, 0, M_SQRT2/2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&p);
	destroy_matrix(&rt);
	destroy_matrix(&irt);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(rotation_axis_y, rotating_a_point_by_half_quarter) {
	t_matrix	*rt = rotation_y(M_PI_4);
	t_matrix	*p = mpoint(1, 0, 0);
	t_matrix	*result = matrixs_product(rt, p);
	t_matrix	*expected_value = mpoint(M_SQRT2/2, 0, -M_SQRT2/2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&p);
	destroy_matrix(&rt);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);

}

Test(rotation_axis_z, rotation_a_point_by_half_quarte) {
	t_matrix	*rt = rotation_z(M_PI_4);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrixs_product(rt, p);
	t_matrix	*expected_value = mpoint(-M_SQRT2/2, M_SQRT2/2, 0);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&rt);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(rotation_axis_z, rotation_a_point_by_half_quarte_to_inversed_way) {
	t_matrix	*rt = rotation_z(M_PI_4);
	t_matrix	*irt = inverse(rt);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrixs_product(irt, p);
	t_matrix	*expected_value = mpoint(M_SQRT2/2, M_SQRT2/2, 0);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&rt);
	destroy_matrix(&irt);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}
