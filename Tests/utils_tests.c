#include <stdbool.h>
#include "utils.h"
#include <math.h>


bool	assert_double_eq(const double f1, const double f2)
{
	return (fabs(f1 - f2 ) < EPISLON);
}

bool	assert_matrices(double result[][4], double expected[][4], unsigned int shape[2])
{
	for (int i = 0; i < (int)shape[0]; i++) {
		for (int j = 0; j < (int)shape[1]; j++) {
			if (!assert_double_eq(result[i][j], expected[i][j]))
				return false;
		}
	}
	return true;
}

