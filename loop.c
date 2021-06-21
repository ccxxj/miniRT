/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 11:32:09 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/30 17:08:16 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* for sp, pl, tr */
void	cal_intersect1(t_object *object, double o[3],
t_result *result, double *dir)
{
	double	t_temp;

	t_temp = INFINITY;
	if (object->type[0] == 's' && object->type[1] == 'p')
		t_temp = cal_sp_intersect(o, object->center, dir, object->diameter[0]);
	else if (object->type[0] == 'p' && object->type[1] == 'l')
		t_temp = cal_pl_intersect(object->center, object->orientation, dir, o);
	else if (object->type[0] == 't' && object->type[1] == 'r')
		t_temp = cal_tr_intersect(object, dir, o);
	if (t_temp > 0 && t_temp < result->t_min)
	{
		result->t_min = t_temp;
		vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);
		if (object->type[0] == 's' && object->type[1] == 'p')
			vector_dir(result->p, object->center, object->orientation);
		vector_multi2(object->rgb, 1, result->rgb);
		update_normal(result->p, o, object->orientation, result->normal);
	}
}

/* for cylinder*/
void	cal_intersect2(t_object *object, double o[3],
t_result *result, double *dir)
{
	double	t_temp;
	double	t_min;

	t_temp = check_side(object, dir, o);
	cal_top_intersect(object, dir, o);
	normalization(dir);
	cal_bottom_intersect(object, dir, o);
	normalization(dir);
	t_min = get_t(object);
	if (t_temp < t_min && t_temp > 0 && t_temp < result->t_min)
	{
		result->t_min = t_temp;
		vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);
		cy_normal(result->p, object);
		vector_multi2(object->rgb, 1, result->rgb);
		update_normal(result->p, o, object->coordinates_3, result->normal);
	}
	else if (t_min < t_temp && t_min > 0 && t_min < result->t_min)
	{
		result->t_min = t_min;
		vector_plus(o, vector_multi2(dir, t_min, result->p), result->p);
		vector_multi2(object->rgb, 1, result->rgb);
		update_normal(result->p, o, object->orientation, result->normal);
	}
}

/*for sq*/
void	cal_intersect3(t_object *object, double o[3],
t_result *result, double *dir)
{
	double	t_temp;

	t_temp = INFINITY;
	t_temp = cal_pl_intersect(object->coordinates_1, object->orientation,
			dir, o);
	if (t_temp > 0 && t_temp < result->t_min)
	{
		process_square(object);
		if (check_sq_intersect(t_temp, object, dir, o) == 1)
		{
			result->t_min = t_temp;
			normalization(dir);
			vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);
			vector_multi2(object->rgb, 1, result->rgb);
			update_normal(result->p, o, object->orientation, result->normal);
		}
	}
}

void	loop_obj(t_object *head, double o[3], double *pri_ray, t_result *result)
{
	while (head)
	{
		pri_ray = normalization(pri_ray);
		if ((head->type[0] == 's' && head->type[1] == 'p')
			|| (head->type[0] == 'p' && head->type[1] == 'l')
			|| (head->type[0] == 't' && head->type[1] == 'r'))
			cal_intersect1(head, o, result, pri_ray);
		if (head->type[0] == 'c' && head->type[1] == 'y')
			cal_intersect2(head, o, result, pri_ray);
		if (head->type[0] == 's' && head->type[1] == 'q')
			cal_intersect3(head, o, result, pri_ray);
		head = head->next;
	}
}

int	cal_return(t_object *objects, t_camera *camera,
t_light *light, t_setting *setting)
{
	double		*pri_ray;
	t_object	*head;
	int			color;
	t_result	result;

	create_vector(&pri_ray);
	head = objects;
	result.t_min = INFINITY;
	pri_ray = cast_ray(camera, setting->pix[0], setting->pix[1], pri_ray);
	loop_obj(head, camera->coordinates, pri_ray, &result);
	color = cal_return2(&result, light, setting, objects);
	free(pri_ray);
	return (color);
}
