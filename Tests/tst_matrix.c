#include "../src/matrix.h"
#include <X11/X.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdbool.h>
#include <stdlib.h>

Test(matrix, expected_a_square_matrix_4) {
	t_tuple	t1 = tuple(1, 2, 3, 4);
	t_tuple	t2 = tuple(5.5, 6.5, 7.5, 8.5);
	t_tuple	t3 = tuple(9, 10, 11, 12);
	t_tuple	t4 = tuple(13.5, 14.5, 15.5, 16.5);
	t_matrix *M = matrix((t_tuple[]){t1, t2, t3, t4}, (unsigned int[]){4, 4});
	float mt[4][4] = {{1., 2., 3., 4.},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}};
	for (int i = 0; i < (int)M->shape[0]; i++) {
		for (int j = 0; j < (int)M->shape[1]; j++) {
			cr_assert_float_eq(mt[i][j], M->mtx[i][j], 0.00001);
		}
	}
	destroy_matrix(&M);
}

Test(matrix, expected_a_square_matrix_2)
{
	t_tuple	t1 = tuple(1, 2, 0, 0);
	t_tuple	t2 = tuple(5.5, 6.5, 0, 0);
	t_matrix	*M = matrix((t_tuple []){t1, t2}, (unsigned int[]){2, 2});
	float mt[2][2] = {{1., 2.}, {5.5, 6.5}};
	for (int i = 0; i < (int)M->shape[0]; i++) {
		for (int j = 0; j < (int)M->shape[1]; j++) {
			cr_assert_float_eq(mt[i][j], M->mtx[i][j], 0.00001);
		}
	}
	destroy_matrix(&M);
}

Test(matrix, expected_a_square_matrix_3) {
	t_matrix	*M = matrix((t_tuple []){
			tuple(15.5, 14.5, 13.5, 0),
			tuple(1, 2, 3, 0),
			tuple(4, 13.5, 5, 0)
			}, (unsigned int[]){3, 3});
	float	mt[3][3] = {{15.5, 14.5, 13.5}, {1, 2, 3}, {4, 13.5, 5}};
	for (int i = 0; i < (int)M->shape[0]; i++) {
		for (int j = 0; j < (int)M->shape[1]; j++) {
			cr_assert_float_eq(mt[i][j], M->mtx[i][j], 0.00001);
		}
	}
	destroy_matrix(&M);
}

Test(eq_matrixes, expected_two_square_matrixes_4_to_be_eqs) {
	t_matrix	*m1 = matrix((t_tuple []){
			tuple(1, 2, 3, 4),
			tuple(5, 6, 7, 8),
			tuple(9, 8, 7, 6),
			tuple(5, 4, 3, 2)
			}, (unsigned int []){4, 4});
	t_matrix	*m2 = matrix((t_tuple []){
			tuple(1, 2, 3, 4),
			tuple(5, 6, 7, 8),
			tuple(9, 8, 7, 6),
			tuple(5, 4, 3, 2)
			}, (unsigned int []){4, 4});
	cr_assert(assert_t_matrix_eq(m1, m2) == true);
	destroy_matrix(&m1);
	destroy_matrix(&m2);
}

Test(eq_matrixes, expected_two_square_matrix_2_to_not_be_eqs) {
	t_matrix	*m1 = matrix((t_tuple []){
			tuple(1, 3, 0, 0),
			tuple(5, 6, 0, 0)
			}, (unsigned int []){2, 2});
	t_matrix	*m2 = matrix((t_tuple []){
			tuple(1, 3, 0, 0),
			tuple(6, 5, 0, 0)
			}, (unsigned int []){2, 2});
	cr_assert(assert_t_matrix_eq(m1, m2) == false);
	destroy_matrix(&m1);
	destroy_matrix(&m2);
}

Test(matrix_product, expected_result_from_matrixes_product_eq_expected_value){
	t_matrix *m1 = matrix((t_tuple []){
			tuple(1, 2, 3, 0),
			tuple(4, 5, 6, 0)
			}, (unsigned int []){2, 3});
	t_matrix *m2 = matrix((t_tuple []){
			tuple(1, 4, 0, 0),
			tuple(2, 5, 0, 0),
			tuple(3, 6, 0, 0)
			}, (unsigned int []){3, 2});
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(14, 32, 0, 0),
			tuple(32, 77, 0, 0)
			}, (unsigned int []){2, 2});
	t_matrix	*result = matrices_product(m1, m2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
	destroy_matrix(&m1);
	destroy_matrix(&m2);
}

Test(transposing, expected_matrix_transposing_from_m) {
	t_matrix	*m = matrix((t_tuple []){
			tuple(1, 2, 3, 4),
			tuple(5, 6, 7, 8)
			}, (unsigned int []){2, 4});
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(1, 5, 0, 0),
			tuple(2, 6, 0, 0),
			tuple(3, 7, 0, 0),
			tuple(4, 8, 0, 0)
			}, (unsigned int []){4,2});
	t_matrix *result = tranposing(m);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&m);
	destroy_matrix(&expected_value);
	destroy_matrix(&result);
}

Test(tranposing, expected_matrix_transposing_from_m1) {
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(1, 0, 0, 0),
			tuple(0, 1, 0, 0),
			tuple(0, 0, 1, 0),
			tuple(0, 0, 0, 1)
			}, (unsigned int []){4,4});
	t_matrix	*m = matrix((t_tuple []){
			tuple(1, 0, 0, 0),
			tuple(0, 1, 0, 0),
			tuple(0, 0, 1, 0),
			tuple(0, 0, 0, 1)
			}, (unsigned int []){4,4});
	t_matrix	*t = tranposing(m);
	cr_assert(assert_t_matrix_eq(t, expected_value) == true);
	destroy_matrix(&t);
	destroy_matrix(&m);
	destroy_matrix(&expected_value);
}

Test(determinant_2, expected_value_17) {
	t_matrix *m = matrix((t_tuple []){
			tuple(1, 5, 0, 0),
			tuple(-3, 2, 0, 0)
			}, (unsigned int []){2, 2});
	cr_assert_float_eq(determinant_2(m), 17., 0.00001);
	destroy_matrix(&m);
}

Test(submatrices, expected_square_matrix2_from_square_matrix3){
	t_matrix	*m3 = matrix((t_tuple []){
			tuple(1, 2, 3, 0),
			tuple(4, 5, 6, 0),
			tuple(7, 8, 9, 0)
			}, (unsigned int []){3, 3});
	t_matrix *result = submatrix(m3, 0, 2);
	t_matrix *expected_value = matrix((t_tuple []){
			tuple(4, 5, 0, 0),
			tuple(7, 8, 0, 0)
			}, (unsigned int []){2, 2});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	cr_assert_eq(result->shape[0], 2);
	cr_assert_eq(result->shape[1], 2);
	destroy_matrix(&m3);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(submatrices, expected_matrix3_from_square_matrix4) {
	t_matrix *m4 = matrix((t_tuple []){
			tuple(1, 2, 3, 2),
			tuple(4, 5, 6, 3),
			tuple(7, 8, 9, 4),
			tuple(10, 28, 34, 12)
			}, (unsigned int []){4, 4});
	t_matrix *result = submatrix(m4, 1, 2);
	t_matrix *expected_value = matrix((t_tuple []){
			tuple(1, 2, 2, 0),
			tuple(7, 8, 4, 0),
			tuple(10, 28, 12, 0)
			}, (unsigned int []){3, 3});
	cr_assert(assert_t_matrix_eq(expected_value, result) == true);
	cr_assert_float_eq(result->shape[0], 3, 0.00001);
	cr_assert_float_eq(result->shape[1], 3, 0.00001);
	destroy_matrix(&expected_value);
	destroy_matrix(&m4);
	destroy_matrix(&result);
}

Test(minor, expected_determinat_from_submatrix_of_A) {
	t_matrix	*A = matrix((t_tuple []){
			tuple(3, 5, 0, 0),
			tuple(2, -1, -7, 0),
			tuple(6, -1, 5, 0)
			}, (unsigned int []){3, 3});
	float result = minor(A, 1, 0);
	float expected_value = 25;
	cr_assert_float_eq(result, expected_value, 0.00001);
	destroy_matrix(&A);
}

Test(cofactor, expected_value_of_cofactor_of_A_0_0) {
	t_matrix	*A = matrix((t_tuple []){
			tuple(3, 5, 0, 0),
			tuple(2, -1, -7, 0),
			tuple(6, -1, 5, 0)
			}, (unsigned int []){3, 3});
	float expected_value = -12;
	float result = cofactor(A, 0, 0);
	cr_assert_float_eq(expected_value, result, 0.00001);
	destroy_matrix(&A);
}

Test(cofactor, expected_value_of_cofactor_of_A_1_0) {
	t_matrix	*A = matrix((t_tuple []){
			tuple(3, 5, 0, 0),
			tuple(2, -1, -7, 0),
			tuple(6, -1, 5, 0)
			}, (unsigned int []){3, 3});
	float expected_value = -25;
	float result = cofactor(A, 1, 0);
	cr_assert_float_eq(expected_value, result, 0.00001);
	destroy_matrix(&A);
}

Test(determinant, expected_the_determinat_of_matrix_A3) {
	t_matrix	*A = matrix((t_tuple []){
			tuple(1, 2, 6, 0),
			tuple(-5, 8, -4, 0),
			tuple(2, 6, 4, 0)
			}, (unsigned int []){3, 3});
	float result = determinant(A);
	float expected_value = -196;
	cr_assert_float_eq(result, expected_value, 0.00001);
	destroy_matrix(&A);
}

Test(determinant, expected_the_determinat_of_matrix_A4) {
	t_matrix	*A = matrix((t_tuple []){
			tuple(-2, -8, 3, 5),
			tuple(-3, 1, 7, 3),
			tuple(1, 2, -9, 6),
			tuple(-6, 7, 7, -9)
			}, (unsigned int []){4, 4});
	float result = determinant(A);
	float expected_value = -4071;
	cr_assert_float_eq(result, expected_value, 0.00001);
	destroy_matrix(&A);
}

Test(inversed_matrix, expected_inversed_matrix_of_A)
{
	t_matrix	*A = matrix((t_tuple []){
			tuple(-5, 2, 6, -8),
			tuple(1, -5, 1, 8),
			tuple(7, 7, -6, -7),
			tuple(1, -3, 7, 4)
			}, (unsigned int []){4, 4});
	t_matrix	*result = inverse(A);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(0.21805, 0.45113, 0.24060, -0.04511),
			tuple(-0.80827, -1.45677, -0.44361, 0.52068),
			tuple(-0.07895, -0.22368, -0.05263, 0.19737),
			tuple(-0.52256, -0.81391, -0.30075, 0.30639)
			}, (unsigned int []){4, 4});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&A);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(inverse, expected_inversed_matrix_of_A1)
{
	t_matrix	*A = matrix((t_tuple []){
			tuple(8, -5, 9, 2),
			tuple(7, 5, 6, 1),
			tuple(-6, 0, 9, 6),
			tuple(-3, 0, -9, -4)
			}, (unsigned int []){4, 4});
	t_matrix	*result = inverse(A);
	t_matrix	*expected_value = matrix((t_tuple []){
			tuple(-0.15385, -0.15385, -0.28205, -0.53846),
			tuple(-0.07692, 0.12308, 0.02564, 0.03077),
			tuple(0.35897, 0.35897, 0.43590, 0.92308),
			tuple(-0.69231, -0.69231, -0.76923, -1.92308)
			}, (unsigned int []){4, 4});
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&A);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(inverse, expected_null_value)
{
	t_matrix	*A = matrix((t_tuple []){
			tuple(-4, 2, -2, 3),
			tuple(9, 6, 2, 6),
			tuple(0, -5, 1, -5),
			tuple(0, 0, 0, 0)
			}, (unsigned int []){4, 4});
	t_matrix	*result = inverse(A);
	cr_assert_null(result);
	destroy_matrix(&A);
}

Test(inverse, expected_matrix_A) {
	t_matrix *A = matrix((t_tuple []){
			tuple(3, -9, 7, 3),
			tuple(3, -8, 2, -9),
			tuple(-4, 4, 4, 1),
			tuple(-6, 5, -1, 1)
			}, (unsigned int []){4, 4});
	t_matrix *B = matrix((t_tuple []){
			tuple(8, 2, 2, 2),
			tuple(3, -1, 7, 0),
			tuple(7, 0, 5, 4),
			tuple(6, -2, 0, 5)
			}, (unsigned int []){4, 4});
	t_matrix *C = matrices_product(A, B);
	t_matrix *iB = inverse(B);
	t_matrix *D = matrices_product(C, iB);
	cr_assert(assert_t_matrix_eq(D, A) == true);
	destroy_matrix(&A);
	destroy_matrix(&B);
	destroy_matrix(&C);
	destroy_matrix(&D);
	destroy_matrix(&iB);
}

Test(inverse, check_if_the_tranposing_of_the_inverse_is_eq_the_inverse_of_the_transposed) {
	t_matrix	*A = matrix((t_tuple []){
			tuple(8, -5, 9, 2),
			tuple(7, 5, 6, 1),
			tuple(-6, 0, 9, 6),
			tuple(-3, 0, -9, -4)
			}, (unsigned int []){4, 4});
	t_matrix	*tranposed_inversed = tranposing(inverse(A));
	t_matrix	*inversed_transposed = inverse(tranposing(A));
	cr_assert(
			assert_t_matrix_eq(tranposed_inversed, inversed_transposed) == true);
	destroy_matrix(&A);
	destroy_matrix(&tranposed_inversed);
	destroy_matrix(&inversed_transposed);
}
