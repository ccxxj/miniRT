/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 16:39:35 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:08:03 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	transfer_rgb(double *rgb, double *intensity, double ratio)
{
	intensity[0] = rgb[0] / 255 * ratio;
	intensity[1] = rgb[1] / 255 * ratio;
	intensity[2] = rgb[2] / 255 * ratio;
}

void	final_intensity(t_result *result)
{
	result->intensity[0] = result->ambient[0] + result->intensity[0];
	result->intensity[1] = result->ambient[1] + result->intensity[1];
	result->intensity[2] = result->ambient[2] + result->intensity[2];
	if (result->intensity[0] > 1)
		result->intensity[0] = 1;
	if (result->intensity[1] > 1)
		result->intensity[1] = 1;
	if (result->intensity[2] > 1)
		result->intensity[2] = 1;
}

int	cal_color(double intensity[3], int t, double rgb[3])
{
	rgb[0] = intensity[0] * rgb[0];
	rgb[1] = intensity[1] * rgb[1];
	rgb[2] = intensity[2] * rgb[2];
	return (create_trgb(t, rgb[0], rgb[1], rgb[2]));
}

int	check_light_intersect(t_light *light, t_result *result, t_object *object,
t_setting *setting)
{
	double		*light_ray;
	t_result	result1;
	double		tcomp;

	vector_multi(setting->rgb, 1);
	create_vector(&light_ray);
	result1.t_min = INFINITY;
	vector_plus(result->p, vector_multi(result->normal, 1e-4), result->p);
	vector_dir(light->coordinates, result->p, light_ray);
	tcomp = sqrt(dot_product(light_ray, light_ray));
	loop_obj(object, result->p, light_ray, &result1);
	if (result1.t_min > tcomp)
	{
		vector_multi(light_ray, -1);
		cal_shade(result, light_ray);
		transfer_rgb(light->rgb, result->diffuse, result->shade);
		vector_multi(result->diffuse, light->brightness[0]);
	}
	else
		transfer_rgb(light->rgb, result->diffuse, 0);
	free(light_ray);
	return (1);
}
