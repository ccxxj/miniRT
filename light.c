/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 16:39:35 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/20 17:14:52 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// cal_reflection(double *normal, double *light_ray, double *reflection)
// {
// 	vect_multi2(normal, 2 * dot_product(normal, light_ray), reflection);
// 	vector_dir(reflection, light_ray, reflection);
// }

void transfer_rgb(double *rgb, double *intensity, double ratio)
{
	intensity[0] = rgb[0] / 255 * ratio;
	intensity[1] = rgb[1] / 255 * ratio;
	intensity[2] = rgb[2] / 255 * ratio;
}

void final_intensity(t_result *result)
{
	result->intensity[0] = result->ambient[0] + result->diffuse[0];
	result->intensity[1] = result->ambient[1] + result->diffuse[1];
	result->intensity[2] = result->ambient[2] + result->diffuse[2];
	if (result->intensity[0] > 1)
		result->intensity[0] = 1;
	if (result->intensity[1] > 1)
		result->intensity[1] = 1;
	if (result->intensity[2] > 1)
		result->intensity[2] = 1;
	
}

int		cal_color(double intensity[3], int t, int r, int g, int b)
{
	r = intensity[0] * r;
	g = intensity[1] * g;
	b = intensity[2] * b;
	return (create_trgb(t, r, g, b));
}
