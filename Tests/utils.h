#ifndef UTILS_H
# define UTILS_H
# define EPISLON 0.00001
#include "../src/objects/object.h"

bool	assert_double_eq(const double f1, const double f2);
bool	assert_matrices(double result[][4], double expected[][4], unsigned int shape[2]);
t_obj	*cpyobj(t_obj *src);
#endif