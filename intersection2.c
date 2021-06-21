/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 09:44:20 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/24 11:34:42 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cy_normal(double *p, t_object *object)
{
	vector_dir(p, object->center, object->coordinates_1);
	object->tri_vect1[0] = dot_product(object->coordinates_1,
			object->orientation);
	vector_multi2(object->orientation, object->tri_vect1[0],
		object->coordinates_2);
	vector_dir(object->coordinates_1, object->coordinates_2,
		object->coordinates_3);
	normalization(object->coordinates_3);
}

void	cal_shade(t_result *result, double light_ray[3])
{
	normalization(result->normal);
	normalization(light_ray);
	result->shade = -dot_product(light_ray, result->normal);
	if (result->shade < 0)
		result->shade = 0;
}
