#include "../src/matrix.h"
#include <X11/X.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
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
			cr_assert_float_eq(mt[i][j], M->M[i][j], 0.00001);
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
			cr_assert_float_eq(mt[i][j], M->M[i][j], 0.00001);
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
			cr_assert_float_eq(mt[i][j], M->M[i][j], 0.00001);
		}
	}
	destroy_matrix(&M);
}
