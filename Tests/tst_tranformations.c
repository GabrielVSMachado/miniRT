#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <math.h>
#include <stdbool.h>
#include "../src/matrix.h"

Test(translation, expected_a_point) {
	t_matrix	*trans = translate(5, -3, 2);
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
	t_matrix	*trans = translate(5, -3, 2);
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
	t_matrix	*trans = translate(5, -3, 2);
	t_matrix	*result = matrixs_product(trans, v);
	cr_assert(assert_t_matrix_eq(result, v) == true);
	destroy_matrix(&v);
	destroy_matrix(&trans);
	destroy_matrix(&result);
}

Test(scaling, expected_the_point_scaled_by_the_matrix_A) {
	t_matrix *A = scale(2, 3, 4);
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
	t_matrix *A = scale(2, 3, 4);
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
	t_matrix *A = inverse(scale(2, 3, 4));
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
	t_matrix	*scl = scale(-1, 1, 1);
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

Test(shearing, shearing1) {
	t_matrix	*sh = shearing((int []){1, 0, 0, 0, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrixs_product(sh, p);
	t_matrix	*expected_value = mpoint(5, 3, 4);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&sh);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(shearing, shearing2) {
	t_matrix	*sh = shearing((int []){0, 1, 0, 0, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrixs_product(sh, p);
	t_matrix	*expected_value = mpoint(6, 3, 4);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&sh);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(shearing, shearing3) {
	t_matrix	*sh = shearing((int []){0, 0, 1, 0, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrixs_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 5, 4);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&sh);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(shearing, shearing4) {
	t_matrix	*sh = shearing((int []){0, 0, 0, 1, 0, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrixs_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 7, 4);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&sh);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(shearing, shearing5) {
	t_matrix	*sh = shearing((int []){0, 0, 0, 0, 1, 0});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrixs_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 3, 6);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&sh);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
}

Test(shearing, shearing6) {
	t_matrix	*sh = shearing((int []){0, 0, 0, 0, 0, 1});
	t_matrix	*p = mpoint(2, 3, 4);
	t_matrix	*result = matrixs_product(sh, p);
	t_matrix	*expected_value = mpoint(2, 3, 7);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&sh);
	destroy_matrix(&p);
	destroy_matrix(&result);
	destroy_matrix(&expected_value);
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
		result = matrixs_product(tmp[i], p);
		cr_assert(assert_t_matrix_eq(result, expected_value[i]) == true);
		destroy_matrix(&p);
		p = result;
	}
	for (int i = 0; i < 3; i++) {
		destroy_matrix(&expected_value[i]);
		destroy_matrix(&tmp[i]);
	}
	destroy_matrix(&result);
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
	composed_transformation = matrixs_product(transf[1], transf[0]);
	tmp = composed_transformation;
	composed_transformation = matrixs_product(transf[2],
			composed_transformation);
	destroy_matrix(&tmp);
	t_matrix	*result = matrixs_product(composed_transformation, p);
	t_matrix	*expected_value = mpoint(15, 0, 7);
	cr_assert(assert_t_matrix_eq(result, expected_value) == true);
	destroy_matrix(&composed_transformation);
	destroy_matrix(&result);
	destroy_matrix(&p);
	for (int i = 0; i < 3; i++) {
		destroy_matrix(&transf[i]);
	}
}
