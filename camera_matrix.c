/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera_matrix.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/15 13:45:33 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/24 14:51:19 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* handle exception of rotation, when camera look at y axis*/
void	exp_handle(double right[3], double up[3], double o)
{
	if (o == 1)
	{
		right[0] = 1;
		up[2] = -1;
	}
	else
	{
		right[0] = -1;
		up[2] = 1;
	}
	right[1] = 0;
	right[2] = 0;
	up[0] = 0;
	up[1] = 0;
}

void	camera_set(t_camera *camera, t_setting *setting)
{
	double	half_width;
	double	half_height;

	if (camera->orientation[1] == 1 || camera->orientation[1] == -1)
		exp_handle(camera->right, camera->up, camera->orientation[1]);
	else
	{
		camera->up[0] = 0;
		camera->up[1] = 1;
		camera->up[2] = 0;
		cross_product(camera->orientation, camera->up, camera->right);
		normalization(camera->right);
		cross_product(camera->right, camera->orientation, camera->up);
		normalization(camera->up);
	}
	half_width = tan(camera->fov[0] * M_PI / 2 / 180);
	half_height = setting->size[1] / setting->size[0] * half_width;
	vector_dir(camera->orientation, vector_multi(camera->up, half_height),
		camera->bottom_left);
	vector_dir(camera->bottom_left, vector_multi(camera->right, half_width),
		camera->bottom_left);
	vector_multi2(camera->right, 2 / setting->size[0], camera->x_unit);
	vector_multi2(camera->up, 2 / setting->size[1], camera->y_unit);
}

double	*cast_ray(t_camera *camera, int x, int y, double *pri_ray)
{
	double	*x_temp;
	double	*y_temp;

	x_temp = NULL;
	y_temp = NULL;
	create_vector(&x_temp);
	create_vector(&y_temp);
	pri_ray = vector_plus(camera->bottom_left,
			vector_multi2(camera->x_unit, x, x_temp), pri_ray);
	pri_ray = vector_plus(pri_ray,
			vector_multi2(camera->y_unit, y, y_temp), pri_ray);
	free(x_temp);
	free(y_temp);
	return (pri_ray);
}
