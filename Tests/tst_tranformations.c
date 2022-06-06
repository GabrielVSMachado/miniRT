#include <criterion/criterion.h>
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
