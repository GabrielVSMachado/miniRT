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
	t_matrix	*result = matrixs_product(m1, m2);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
	destroy_matrix(&m1);
	destroy_matrix(&m2);
}
