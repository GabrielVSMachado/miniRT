#include <stdbool.h>
#include "utils.h"
#include <stdlib.h>
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

// static void	cpymatrices(t_matrix *dst, t_matrix *src)
// {
// 	int	counter;

// 	counter = -1;
// 	while (++counter < (int)src->shape[0])
// 	{
// 		dst->mtx[counter][0] = src->mtx[counter][0];
// 		dst->mtx[counter][1] = src->mtx[counter][1];
// 		dst->mtx[counter][2] = src->mtx[counter][2];
// 		dst->mtx[counter][3] = src->mtx[counter][3];
// 	}
// 	dst->shape[0] = src->shape[0];
// 	dst->shape[1] = src->shape[1];
// }


// t_obj	*cpyobj(t_obj *src)
// {
// 	t_obj	*cpy;

// 	cpy = new_object(src->type);
// 	cpy->material->ambient = src->material->ambient;
// 	cpy->material->diffuse = src->material->diffuse;
// 	cpy->material->shininess = src->material->shininess;
// 	cpy->material->specular = src->material->specular;
// 	cpy->material->c[0] = src->material->c[0];
// 	cpy->material->c[1] = src->material->c[1];
// 	cpy->material->c[2] = src->material->c[2];
// 	cpy->material->c[3] = src->material->c[3];
// 	cpymatrices(cpy->transform, src->transform);
// 	cpy->inversed_transform = malloc(sizeof(t_matrix));
// 	cpymatrices(cpy->inversed_transform, src->inversed_transform);
// 	cpy->local_intersect = src->local_intersect;
// 	cpy->local_normal_at = src->local_normal_at;
// 	return (cpy);
// }
