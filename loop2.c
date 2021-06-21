/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 12:45:23 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:08:43 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_t(t_object *object)
{
	double	t_min;

	if (object->tri_vect2[0] < object->tri_vect2[1])
		t_min = object->tri_vect2[0];
	else
		t_min = object->tri_vect2[1];
	if (t_min <= 0)
		t_min = INFINITY;
	return (t_min);
}

double	cal_return2(t_result *result, t_light *light,
t_setting *setting, t_object *objects)
{
	t_light		*head_l;
	t_object	*head;
	int			color;

	head = objects;
	if (result->t_min == INFINITY)
		color = create_trgb(0, 0, 0, 0);
	else
	{
		head_l = light;
		result->intensity[0] = 0;
		result->intensity[1] = 0;
		result->intensity[2] = 0;
		while (head_l)
		{
			check_light_intersect(head_l, result, head, setting);
			vector_plus(result->intensity, result->diffuse, result->intensity);
			head_l = head_l->next;
		}
		transfer_rgb(setting->rgb, result->ambient, setting->lighting_r[0]);
		final_intensity(result);
		color = cal_color(result->intensity, 0, result->rgb);
	}
	return (color);
}
