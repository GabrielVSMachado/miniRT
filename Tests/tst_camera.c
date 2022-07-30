#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "../src/camera/camera.h"
#include <math.h>
#include <stdlib.h>
#include "utils.h"

#define EPISLON 0.00001

Test(camera, constructing_a_camera)
{
	t_camera *result = camera(160, 120, M_PI_2);
	cr_assert_float_eq(result->field_of_view, M_PI_2, EPISLON);
	cr_assert_eq(result->hsize, 160);
	cr_assert_eq(result->vsize, 120);
	cr_assert(assert_matrices(result->tranform->mtx, identity()->mtx, (unsigned int [2]){4, 4}));
	destroy_camera(&result);
}

Test(camera, the_pixel_size_for_a_horizontal_canvas)
{
	t_camera *result = camera(200, 125, M_PI_2);
	cr_assert_float_eq(result->pixel_size, 0.01, EPISLON);
	destroy_camera(&result);
}

Test(camera, the_pixel_size_for_a_vertical_canvas)
{
	t_camera	*result = camera(125, 200, M_PI_2);
	cr_assert_float_eq(result->pixel_size, 0.01, EPISLON);
	destroy_camera(&result);
}

// Test(camera, constructing_a_ray_through_the_center_of_the_canvas)
// {
// 	t_camera	*cam = camera(201, 101, M_PI_2);
// 	t_ray		*r = ray_for_pixel(cam, 100, 50);
// 	t_tuple		expected_direction = vector(0, 0, -1);
// 	for (int i = 0; i < 3; i++) {
// 		cr_assert_float_eq(r->origin[i], 0, EPISLON);
// 		cr_assert_float_eq(r->direction[i], expected_direction[i], EPISLON);
// 	}
// 	destroy_matrix(&cam->tranform);
// 	destroy_ray(&r);
// 	free(expected_direction);
// }

// Test(camera, constructing_a_ray_through_a_corner_of_the_canvas)
// {
// 	t_camera	*cam = camera(201, 101, M_PI_2);
// 	t_ray		*r = ray_for_pixel(cam, 0, 0);
// 	t_tuple		expected_direction = vector(0.66519, 0.33259, -0.66851);
// 	for (int i = 0; i < 3; i++) {
// 		cr_assert_float_eq(r->origin[i], 0, EPISLON);
// 		cr_assert_float_eq(r->direction[i], expected_direction[i], EPISLON);
// 	}
// 	destroy_matrix(&cam->tranform);
// 	destroy_ray(&r);
// 	free(expected_direction);
// }

// Test(camera, constructing_a_ray_when_the_camera_is_transformed)
// {
// 	t_camera	*cam = camera(201, 101, M_PI_2);
// 	transform_camera(cam, matrices_product(rotation_y(M_PI_4),
// 				translate(0, -2, 5)));
// 	t_ray *r = ray_for_pixel(cam, 100, 50);
// 	double	expected_direction[] = {M_SQRT2 / 2., 0, -M_SQRT2 / 2.};
// 	double	expected_origin[] = {0, 2, -5};
// 	for (int i = 0; i < 3; ++i) {
// 		cr_assert_float_eq(r->origin[i], expected_origin[i], EPISLON);
// 		cr_assert_float_eq(r->direction[i], expected_direction[i], EPISLON);
// 	}
// }
