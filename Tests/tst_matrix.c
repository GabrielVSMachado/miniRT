#include "../src/vectors/vectors.h"
#include <X11/X.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "utils.h"

Test(matrix, expected_a_square_matrix_4) {
	t_matrix *M = matrix((double [][4]){
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}
	}, (unsigned int[]){4, 4});
	double mt[4][4] = {{1., 2., 3., 4.},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}};
	cr_assert_eq(assert_matrices(M->mtx, mt, M->shape), true);
	free(M);
}

Test(matrix, expected_a_square_matrix_2)
{
	t_matrix	*M = matrix((double [][4]){
		{1, 2, 0, 0},
		{5.5, 6.5, 0, 0}
		}, (unsigned int[]){2, 2});
	double mt[][4] = {{1., 2., 0, 0}, {5.5, 6.5, 0, 0}};
	cr_assert_eq(assert_matrices(M->mtx, mt, M->shape), true);
	free(M);
}

Test(matrix, expected_a_square_matrix_3) {
	t_matrix	*M = matrix((double [][4]){
			{15.5, 14.5, 13.5, 0},
			{1, 2, 3, 0},
			{4, 13.5, 5, 0}
			}, (unsigned int[]){3, 3});
	double	mt[][4] = {{15.5, 14.5, 13.5, 0.}, {1, 2, 3, 0}, {4, 13.5, 5, 0}};
	cr_assert_eq(assert_matrices(M->mtx, mt, M->shape), true);
	free(M);
}

Test(matrix, expected_values_out_of_range_eq_zero)
{
	t_matrix	*m = matrix((double [][4]){{1, 0, 0, 0}}, (unsigned int []){1, 1});
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
			cr_assert_float_eq(m->mtx[i][j], 0, 0.00001);
	}
	free(m);
}

Test(matrix_product, expected_result_from_matrixes_product_eq_expected_value){
	t_matrix *m1 = matrix((double [][4]){
			{1, 2, 3, 0},
			{4, 5, 6, 0}
			}, (unsigned int []){2, 3});
	t_matrix *m2 = matrix((double [][4]){
			{1, 4, 0, 0},
			{2, 5, 0, 0},
			{3, 6, 0, 0}
			}, (unsigned int []){3, 2});
	t_matrix	*expected_value = matrix((double [][4]){
			{14, 32, 0, 0},
			{32, 77, 0, 0}
			}, (unsigned int []){2, 2});
	t_matrix	*result = matrices_product(m1, m2);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(result);
	free(m1);
	free(m2);
	free(expected_value);
}

Test(transposing, expected_matrix_transposing_from_m) {
	t_matrix	*m = matrix((double [][4]){
			{1, 2, 3, 4},
			{5, 6, 7, 8}
			}, (unsigned int []){2, 4});
	t_matrix	*expected_value = matrix((double [][4]){
			{1, 5, 0, 0},
			{2, 6, 0, 0},
			{3, 7, 0, 0},
			{4, 8, 0, 0}
			}, (unsigned int []){4,2});
	t_matrix *result = tranposing(m);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(m);
	free(expected_value);
	free(result);
}

Test(tranposing, expected_matrix_transposing_from_m1) {
	t_matrix	*expected_value = matrix((double [][4]){
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
			}, (unsigned int []){4,4});
	t_matrix	*m = matrix((double [][4]){
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
			}, (unsigned int []){4,4});
	t_matrix	*t = tranposing(m);
	cr_assert(assert_matrices(t->mtx, expected_value->mtx, expected_value->shape) == true);
	free(t);
	free(m);
	free(expected_value);
}

Test(determinant_2, expected_value_17) {
	t_matrix *m = matrix((double [][4]){
			{1, 5, 0, 0},
			{-3, 2, 0, 0}
			}, (unsigned int []){2, 2});
	cr_assert_float_eq(determinant_2(m), 17., 0.00001);
	free(m);
}

Test(submatrices, expected_square_matrix2_from_square_matrix3){
	t_matrix	*m3 = matrix((double [][4]){
			{1, 2, 3, 0},
			{4, 5, 6, 0},
			{7, 8, 9, 0}
			}, (unsigned int []){3, 3});
	t_matrix *result = submatrix(m3, 0, 2);
	t_matrix *expected_value = matrix((double [][4]){
			{4, 5, 0, 0},
			{7, 8, 0, 0}
			}, (unsigned int []){2, 2});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	cr_assert_eq(result->shape[0], 2);
	cr_assert_eq(result->shape[1], 2);
	free(result);
	free(expected_value);
	free(m3);
}

Test(submatrices, expected_matrix3_from_square_matrix4) {
	t_matrix *m4 = matrix((double [][4]){
			{1, 2, 3, 2},
			{4, 5, 6, 3},
			{7, 8, 9, 4},
			{10, 28, 34, 12}
			}, (unsigned int []){4, 4});
	t_matrix *result = submatrix(m4, 1, 2);
	t_matrix *expected_value = matrix((double [][4]){
			{1, 2, 2, 0},
			{7, 8, 4, 0},
			{10, 28, 12, 0}
			}, (unsigned int []){3, 3});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	cr_assert_float_eq(result->shape[0], 3, EPISLON);
	cr_assert_float_eq(result->shape[1], 3, EPISLON);
	free(expected_value);
	free(m4);
	free(result);
}

Test(minor, expected_determinat_from_submatrix_of_A) {
	t_matrix	*A = matrix((double [][4]){
			{3, 5, 0, 0},
			{2, -1, -7, 0},
			{6, -1, 5, 0}
			}, (unsigned int []){3, 3});
	double result = minor(A, 1, 0);
	double expected_value = 25;
	cr_assert_float_eq(result, expected_value, EPISLON);
	free(A);
}

Test(cofactor, expected_value_of_cofactor_of_A_0_0) {
	t_matrix	*A = matrix((double [][4]){
			{3, 5, 0, 0},
			{2, -1, -7, 0},
			{6, -1, 5, 0}
			}, (unsigned int []){3, 3});
	double expected_value = -12;
	double result = cofactor(A, 0, 0);
	cr_assert_float_eq(expected_value, result, EPISLON);
	free(A);
}

Test(cofactor, expected_value_of_cofactor_of_A_1_0) {
	t_matrix	*A = matrix((double [][4]){
			{3, 5, 0, 0},
			{2, -1, -7, 0},
			{6, -1, 5, 0}
			}, (unsigned int []){3, 3});
	double expected_value = -25;
	double result = cofactor(A, 1, 0);
	cr_assert_float_eq(expected_value, result, EPISLON);
	free(A);
}

Test(determinant, expected_the_determinat_of_matrix_A3) {
	t_matrix	*A = matrix((double [][4]){
			{1, 2, 6, 0},
			{-5, 8, -4, 0},
			{2, 6, 4, 0}
			}, (unsigned int []){3, 3});
	double result = determinant(A);
	double expected_value = -196;
	cr_assert_float_eq(result, expected_value, EPISLON);
	free(A);
}

Test(determinant, expected_the_determinat_of_matrix_A4) {
	t_matrix	*A = matrix((double [][4]){
			{-2, -8, 3, 5},
			{-3, 1, 7, 3},
			{1, 2, -9, 6},
			{-6, 7, 7, -9}
			}, (unsigned int []){4, 4});
	double result = determinant(A);
	double expected_value = -4071;
	cr_assert_float_eq(result, expected_value, EPISLON);
	free(A);
}

Test(inversed_matrix, expected_inversed_matrix_of_A)
{
	t_matrix	*A = matrix((double [][4]){
			{-5, 2, 6, -8},
			{1, -5, 1, 8},
			{7, 7, -6, -7},
			{1, -3, 7, 4}
			}, (unsigned int []){4, 4});
	t_matrix	*result = inverse(A);
	t_matrix	*expected_value = matrix((double [][4]){
			{0.21805, 0.45113, 0.24060, -0.04511},
			{-0.80827, -1.45677, -0.44361, 0.52068},
			{-0.07895, -0.22368, -0.05263, 0.19737},
			{-0.52256, -0.81391, -0.30075, 0.30639}
			}, (unsigned int []){4, 4});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(A);
	free(result);
	free(expected_value);
}

Test(inverse, expected_inversed_matrix_of_A1)
{
	t_matrix	*A = matrix((double [][4]){
			{8, -5, 9, 2},
			{7, 5, 6, 1},
			{-6, 0, 9, 6},
			{-3, 0, -9, -4},
			}, (unsigned int []){4, 4});
	t_matrix	*result = inverse(A);
	t_matrix	*expected_value = matrix((double [][4]){
			{-0.15385, -0.15385, -0.28205, -0.53846},
			{-0.07692, 0.12308, 0.02564, 0.03077},
			{0.35897, 0.35897, 0.43590, 0.92308},
			{-0.69231, -0.69231, -0.76923, -1.92308},
			}, (unsigned int []){4, 4});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(A);
	free(result);
	free(expected_value);
}

Test(inverse, expected_null_value)
{
	t_matrix	*A = matrix((double [][4]){
			{-4, 2, -2, 3},
			{9, 6, 2, 6},
			{0, -5, 1, -5},
			{0, 0, 0, 0}
			}, (unsigned int []){4, 4});
	t_matrix	*result = inverse(A);
	cr_assert_null(result);
	free(A);
}

Test(inverse, expected_matrix_A) {
	t_matrix *A = matrix((double [][4]){
			{3, -9, 7, 3},
			{3, -8, 2, -9},
			{-4, 4, 4, 1},
			{-6, 5, -1, 1}
			}, (unsigned int []){4, 4});
	t_matrix *B = matrix((double [][4]){
			{8, 2, 2, 2},
			{3, -1, 7, 0},
			{7, 0, 5, 4},
			{6, -2, 0, 5}
			}, (unsigned int []){4, 4});
	t_matrix *C = matrices_product(A, B);
	t_matrix *iB = inverse(B);
	t_matrix *D = matrices_product(C, iB);
	cr_assert(assert_matrices(D->mtx, A->mtx, A->shape) == true);
	free(A);
	free(B);
	free(C);
	free(D);
	free(iB);
}

Test(inverse, check_if_the_tranposing_of_the_inverse_is_eq_the_inverse_of_the_transposed) {
	t_matrix	*A = matrix((double [][4]){
			{8, -5, 9, 2},
			{7, 5, 6, 1},
			{-6, 0, 9, 6},
			{-3, 0, -9, -4}
			}, (unsigned int []){4, 4});
	t_matrix	*tranposed_inversed = tranposing(inverse(A));
	t_matrix	*inversed_transposed = inverse(tranposing(A));
	cr_assert(assert_matrices(tranposed_inversed->mtx, inversed_transposed->mtx, inversed_transposed->shape) == true);
	free(A);
	free(tranposed_inversed);
	free(inversed_transposed);
}
