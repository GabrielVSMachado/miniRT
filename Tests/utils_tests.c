#include <stdbool.h>
#include "utils.h"
#include <math.h>
#include "../src/objects/object.h"


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

t_obj	*cpyobj(t_obj *src)
{
	t_obj	*cpy;
	int		counter;

	cpy = new_object(src->type);
	cpy->material->ambient = src->material->ambient;
	cpy->material->diffuse = src->material->diffuse;
	cpy->material->shininess = src->material->shininess;
	cpy->material->specular = src->material->specular;
	cpy->material->c[0] = src->material->c[0];
	cpy->material->c[1] = src->material->c[1];
	cpy->material->c[2] = src->material->c[2];
	cpy->material->c[3] = src->material->c[3];
	counter = -1;
	while (++counter < (int)src->transform->shape[0])
	{
		cpy->transform->mtx[counter][0] = src->transform->mtx[counter][0];
		cpy->transform->mtx[counter][1] = src->transform->mtx[counter][1];
		cpy->transform->mtx[counter][2] = src->transform->mtx[counter][2];
		cpy->transform->mtx[counter][3] = src->transform->mtx[counter][3];
	}
	cpy->transform->shape[0] = src->transform->shape[0];
	cpy->transform->shape[1] = src->transform->shape[1];
	cpy->inversed_transform = inverse(cpy->transform);
	return (cpy);
}

