/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sq_intersect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/10 19:45:32 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/10 19:46:10 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	process_square(t_object *object)
{
	if (object->orientation[1] == 1 || object->orientation[1] == -1)
		exp_handle(object->coordinates_3, object->coordinates_2, object->orientation[1]);
	else
	{
		object->coordinates_2[0] = 0;
		object->coordinates_2[1] = 1;
		object->coordinates_2[2] = 0;
		cross_product(object->orientation, object->coordinates_2, object->coordinates_3);//need to check exception, when the orientation is along y axis
		normalization(object->coordinates_3);
		cross_product(object->coordinates_3, object->orientation, object->coordinates_2);
		normalization(object->coordinates_2);
	}
}

int		check_sq_intersect(double t, t_object *object, double dir[3], double o[3])
{
	double *ptocenter;
	double a;
	double b;
	double halfsize;

	ptocenter = malloc(3 * sizeof(double));
	if (!ptocenter)
		return (-1);
	vector_plus(o, vector_multi(dir, t), ptocenter);
	vector_dir(object->coordinates_1, ptocenter, ptocenter);
	a = dot_product(ptocenter, object->coordinates_2);
	b = dot_product(ptocenter, object->coordinates_3);
	halfsize = object->lenth[0] / 2;
	free(ptocenter);
	if (a <= halfsize && a >= -halfsize && b <= halfsize && b >= -halfsize)
		return (1);
	else
		return (-1);
}
