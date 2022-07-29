#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdbool.h>
#include "../src/vectors/vectors.h"
#include "utils.h"
#include <math.h>

static t_matrix	*mpoint(t_cordinate	x, t_cordinate y, t_cordinate z)
{
	return (
		matrix((double [][4]){
			{x, 0, 0, 0},
			{y, 0, 0, 0},
			{z, 0, 0, 0},
			{1, 0, 0, 0}
		}, (unsigned int []){4, 1})
	);
}

Test(translation, expected_a_point) {
	t_matrix	*trans = translate(5, -3, 2);
	t_matrix	*m = matrix((double [][4]){
			{-3, 0, 0, 0},
			{4, 0, 0, 0},
			{5, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrices_product(trans, m);
	t_matrix	*expected_value = matrix((double [][4]){
			{2, 0, 0, 0},
			{1, 0, 0, 0},
			{7, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(trans);
	free(m);
	free(result);
	free(expected_value);
}

Test(translation, expected_a_point2) {
	t_matrix	*trans = translate(5, -3, 2);
	t_matrix	*itrans = inverse(trans);
	t_matrix	*p = matrix((double [][4]){
			{-3, 0, 0, 0},
			{4, 0, 0, 0},
			{5, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrices_product(itrans, p);
	t_matrix	*expected_value = matrix((double [][4]){
			{-8, 0, 0, 0},
			{7, 0, 0, 0},
			{3, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(trans);
	free(itrans);
	free(p);
	free(result);
	free(expected_value);
}

Test(translation, expected_value_eq_vector) {
	t_matrix	*v = matrix((double [][4]){
			{-3, 0, 0, 0},
			{4, 0, 0, 0},
			{5, 0, 0, 0},
			{0, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*trans = translate(5, -3, 2);
	t_matrix	*result = matrices_product(trans, v);
	cr_assert(assert_matrices(result->mtx, v->mtx, v->shape) == true);
	free(v);
	free(trans);
	free(result);
}
Test(scaling, expected_the_point_scaled_by_the_matrix_A) {
	t_matrix *A = scale(2, 3, 4);
	t_matrix *p = matrix((double [][4]){
			{-4, 0, 0, 0},
			{6, 0, 0, 0},
			{8, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrices_product(A, p);
	t_matrix	*expected_value = matrix((double [][4]){
			{-8, 0, 0, 0},
			{18, 0, 0, 0},
			{32, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(A);
	free(p);
	free(result);
	free(expected_value);
}

Test(scaling, expected_the_vector_scaled_by_the_matrix_A) {
	t_matrix *A = scale(2, 3, 4);
	t_matrix *p = matrix((double [][4]){
			{-4, 0, 0, 0},
			{6, 0, 0, 0},
			{8, 0, 0, 0},
			{0, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrices_product(A, p);
	t_matrix	*expected_value = matrix((double [][4]){
			{-8, 0, 0, 0},
			{18, 0, 0, 0},
			{32, 0, 0, 0},
			{0, 0, 0, 0}
			}, (unsigned int []){4, 1});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(A);
	free(p);
	free(result);
	free(expected_value);
}

Test(scaling, expected_the_point_shrink_by_the_matrix_A)
{
	t_matrix *A = inverse(scale(2, 3, 4));
	t_matrix *p = matrix((double [][4]){
			{-4, 0, 0, 0},
			{6, 0, 0, 0},
			{8, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrices_product(A, p);
	t_matrix	*expected_value = matrix((double [][4]){
			{-2, 0, 0, 0},
			{2, 0, 0, 0},
			{2, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(A);
	free(p);
	free(result);
	free(expected_value);
}

Test(scaling, try_reflect_a_point_in_x_axis) {
	t_matrix	*scl = scale(-1, 1, 1);
	t_matrix	*p = matrix((double [][4]){
			{2, 0, 0, 0},
			{3, 0, 0, 0},
			{4, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	t_matrix	*result = matrices_product(scl, p);
	t_matrix	*expected_value = matrix((double [][4]){
			{-2, 0, 0, 0},
			{3, 0, 0, 0},
			{4, 0, 0, 0},
			{1, 0, 0, 0}
			}, (unsigned int []){4, 1});
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(scl);
	free(result);
	free(expected_value);
	free(p);
}

Test(rotation_axis_x, expected_point_after_rotation_in_half_way_to_axis_z) {
	t_matrix	*rt = rotation_x(M_PI_4);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrices_product(rt, p);
	t_matrix	*expected_value = mpoint(0, M_SQRT2/2,  M_SQRT2/2);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(result);
	free(rt);
	free(p);
	free(expected_value);
}

Test(rotation_axis_x, expected_point_after_rotation_in_axis_z)
{
	t_matrix	*rt = rotation_x(M_PI_2);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrices_product(rt, p);
	t_matrix	*expected_value = mpoint(0, 0, 1);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(result);
	free(rt);
	free(p);
	free(expected_value);

}

Test(rotation_axis_x, expected_point_after_rotation_in_axis_x)
{
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*rt = rotation_x(M_PI_4);
	t_matrix	*irt = inverse(rt);
	t_matrix	*result = matrices_product(irt, p);
	t_matrix	*expected_value = mpoint(0, M_SQRT2/2, -M_SQRT2/2);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(p);
	free(rt);
	free(irt);
	free(result);
	free(expected_value);
}

Test(rotation_axis_y, rotating_a_point_a_positive_half_quarter_of_y_axis)
{
	t_matrix	*rt = rotation_y(M_PI_4);
	t_matrix	*p = mpoint(0, 0, 1);
	t_matrix	*result = matrices_product(rt, p);
	t_matrix	*expected_value = mpoint(M_SQRT2/2, 0, M_SQRT2/2);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(p);
	free(rt);
	free(result);
	free(expected_value);
}

Test(rotation_axis_y, rotating_a_point_a_negative_half_quarter_of_y_axis){
	t_matrix	*rt = rotation_y(M_PI_4);
	t_matrix	*irt = inverse(rt);
	t_matrix	*p = mpoint(0, 0, 1);
	t_matrix	*result = matrices_product(irt, p);
	t_matrix	*expected_value = mpoint(-M_SQRT2/2, 0, M_SQRT2/2);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(p);
	free(rt);
	free(irt);
	free(result);
	free(expected_value);
}

Test(rotation_axis_y, rotating_a_point_by_half_quarter) {
	t_matrix	*rt = rotation_y(M_PI_4);
	t_matrix	*p = mpoint(1, 0, 0);
	t_matrix	*result = matrices_product(rt, p);
	t_matrix	*expected_value = mpoint(M_SQRT2/2, 0, -M_SQRT2/2);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(p);
	free(rt);
	free(result);
	free(expected_value);

}

Test(rotation_axis_z, rotation_a_point_by_half_quarte) {
	t_matrix	*rt = rotation_z(M_PI_4);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrices_product(rt, p);
	t_matrix	*expected_value = mpoint(-M_SQRT2/2, M_SQRT2/2, 0);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(rt);
	free(p);
	free(result);
	free(expected_value);
}

Test(rotation_axis_z, rotation_a_point_by_half_quarte_to_inversed_way) {
	t_matrix	*rt = rotation_z(M_PI_4);
	t_matrix	*irt = inverse(rt);
	t_matrix	*p = mpoint(0, 1, 0);
	t_matrix	*result = matrices_product(irt, p);
	t_matrix	*expected_value = mpoint(M_SQRT2/2, M_SQRT2/2, 0);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(rt);
	free(irt);
	free(p);
	free(result);
	free(expected_value);
}

Test(shearing, shearing1) {
	t_matrix	*sh = shearing((int []){1, 0, 0, 0, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrices_product(sh, p);
	t_matrix	*expected_value = mpoint(5, 3, 4);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(sh);
	free(p);
	free(result);
	free(expected_value);
}

Test(shearing, shearing2) {
	t_matrix	*sh = shearing((int []){0, 1, 0, 0, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrices_product(sh, p);
	t_matrix	*expected_value = mpoint(6, 3, 4);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(sh);
	free(p);
	free(result);
	free(expected_value);
}

Test(shearing, shearing3) {
	t_matrix	*sh = shearing((int []){0, 0, 1, 0, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrices_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 5, 4);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(sh);
	free(p);
	free(result);
	free(expected_value);
}

Test(shearing, shearing4) {
	t_matrix	*sh = shearing((int []){0, 0, 0, 1, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrices_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 7, 4);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(sh);
	free(p);
	free(result);
	free(expected_value);
}

Test(shearing, shearing5) {
	t_matrix	*sh = shearing((int []){0, 0, 0, 0, 1, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrices_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 3, 6);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(sh);
	free(p);
	free(result);
	free(expected_value);
}

Test(shearing, shearing6) {
	t_matrix	*sh = shearing((int []){0, 0, 0, 0, 0, 1});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrices_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 3, 7);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(sh);
	free(p);
	free(result);
	free(expected_value);
}

Test(composing_transformations, individual_apply_transformation) {
	t_matrix	*p = mpoint(1, 0, 1);
	t_matrix	*rt = rotation_x(M_PI_2);
	t_matrix	*scl = scale(5, 5, 5);
	t_matrix	*tcl = translate(10, 5, 7);
	t_matrix	*tmp[3] = {
		rt,
		scl,
		tcl
	};
	t_matrix	*expected_value[3] = {
		mpoint(1, -1, 0),
		mpoint(5, -5, 0),
		mpoint(15, 0, 7)
	};
	t_matrix	*result;
	for (int i = 0; i < 3; i++) {
		result = matrices_product(tmp[i], p);
		cr_assert(assert_matrices(result->mtx, expected_value[i]->mtx, expected_value[i]->shape) == true);
		free(p);
		p = result;
	}
	for (int i = 0; i < 3; i++) {
		free(expected_value[i]);
		free(tmp[i]);
	}
	free(result);
}

Test(composing_transformations, composing_transformations) {
	t_matrix	*p = mpoint(1, 0, 1);
	t_matrix	*transf[3] = {
		rotation_x(M_PI_2),
		scale(5, 5, 5),
		translate(10, 5, 7)
	};
	t_matrix	*composed_transformation;
	t_matrix	*tmp;
	composed_transformation = matrices_product(transf[1], transf[0]);
	tmp = composed_transformation;
	composed_transformation = matrices_product(transf[2],
			composed_transformation);
	free(tmp);
	t_matrix	*result = matrices_product(composed_transformation, p);
	t_matrix	*expected_value = mpoint(15, 0, 7);
	cr_assert(assert_matrices(result->mtx, expected_value->mtx, expected_value->shape) == true);
	free(composed_transformation);
	free(result);
	free(p);
	for (int i = 0; i < 3; i++) {
		free(transf[i]);
	}
}
