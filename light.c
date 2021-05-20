/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/16 16:39:35 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/20 11:17:08 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

cal_reflection(double *normal, double *light_ray, double *reflection)
{
	vect_multi2(normal, 2 * dot_product(normal, light_ray), reflection);
	vector_dir(reflection, light_ray, reflection);
}


void	light_intensity(t_setting *setting, double diffuse)
{
	double	ambient;

	ambient = setting->lighting_r[0];

}