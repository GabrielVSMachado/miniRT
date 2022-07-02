#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <math.h>
#include <stdlib.h>
#include "../src/miniRT.h"

#define EPISLON 0.00001

static	t_vector	r, v, n, expected_value;

void	fini_reflect(void) {
	free(r);
	r = NULL;
	free(n);
	n = NULL;
	free(v);
	v = NULL;
	free(expected_value);
	expected_value = NULL;
}

Test(reflect, reflecting_a_vector_approaching_at_45_degress, .fini=fini_reflect)
{
	v = vector(1, -1, 0);
	n = vector(0, 1, 0);
	r = reflect(v, n);
	expected_value = vector(1, 1, 0);
	for (int i = 0; i < 4; i++)
		cr_assert_float_eq(r[i], expected_value[i], EPISLON);
}

Test(reflect, reflecting_a_vector_off_a_slanted_surface, .fini=fini_reflect)
{
	v = vector(0, -1, 0);
	n = vector(M_SQRT2 / 2., M_SQRT2 / 2., 0);
	r = reflect(v, n);
	expected_value = vector(1, 0, 0);
	for (int i = 0; i < 4; i++)
		cr_assert_float_eq(r[i], expected_value[i], EPISLON);
}
