/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 11:32:09 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/20 17:58:30 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cal_shade(t_result *result, double light_ray[3])
{
	// printf("light ray is is %f %f %f\n", light_ray[0], light_ray[1], light_ray[2]);
	normalization(result->normal);
	normalization(light_ray);
	result->shade = -dot_product(light_ray, result->normal);
	// printf("shade 1 is %f\n", result->shade);
	// printf("light ray is is %f %f %f\n", light_ray[0], light_ray[1], light_ray[2]);
	// printf("normal is is %f %f %f\n", result->normal[0], result->normal[1], result->normal[2]);
	if (result->shade < 0)
		result->shade = 0;
}

void cal_intersect1(t_object *object, double o[3], t_result *result, double *dir)//only for sp, pl, tr
{
	double t_temp;

	t_temp = INFINITY;
	if (object->type[0] == 's' && object->type[1] == 'p')
		t_temp = cal_sp_intersect(o, object->center, dir, object->diameter[0]);
	else if (object->type[0] == 'p' && object->type[1] == 'l')
		t_temp = cal_pl_intersect(object->center, object->orientation, dir, o);
	else if (object->type[0] == 't' && object->type[1] == 'r')
		t_temp = cal_tr_intersect(object, dir, o);
	if (t_temp > 0 && t_temp < result->t_min)//how to treat t=0? when the intersection is on camera
	{
		result->t_min = t_temp;
		vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);//store p vector
		if (object->type[0] == 's' && object->type[1] == 'p')
			vector_dir(result->p, object->center, object->orientation);
		vector_multi2(object->rgb, 1, result->rgb);//store rgb value
		update_normal(result->p, o, object->orientation, result->normal);
	}
}

void cal_intersect2(t_object *object, double o[3], t_result *result, double *dir)
{
	double	t_temp;
	double	t_min;

	t_temp = check_side(object, dir, o);
	// printf("tmin is %f\n", t_temp);
	normalization(dir);//probably not needed, #double check later
	// printf("dir1 is is %f %f %f\n", dir[0], dir[1], dir[2]);
	cal_top_intersect(object, dir, o);
	// printf("dir11 is is %f %f %f\n", dir[0], dir[1], dir[2]);
	normalization(dir);
	cal_bottom_intersect(object, dir, o);
	// printf("dir111 is is %f %f %f\n", dir[0], dir[1], dir[2]);
	normalization(dir);
	if (object->tri_vect2[0] < object->tri_vect2[1])
		t_min = object->tri_vect2[0];
	else
		t_min = object->tri_vect2[1];
	if (t_min <= 0)
		t_min = INFINITY;
	if (t_temp < t_min && t_temp > 0 && t_temp < result->t_min) 
	{
		result->t_min = t_temp;
		vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);
		cy_normal(result->p, object);
		vector_multi2(object->rgb, 1, result->rgb);//store rgb value
		update_normal(result->p, o, object->coordinates_3, result->normal);
	}
	else if (t_min < t_temp && t_min > 0 && t_min < result->t_min)
	{
		result->t_min = t_min;
		vector_plus(o, vector_multi2(dir, t_min, result->p), result->p);//store p vector
		vector_multi2(object->rgb, 1, result->rgb);//store rgb value
		update_normal(result->p, o, object->orientation, result->normal);
	}
}


void cal_intersect3(t_object *object, double o[3], t_result *result, double *dir)//only for sq
{
	double t_temp;

	t_temp = INFINITY;

	t_temp = cal_pl_intersect(object->coordinates_1, object->orientation, dir, o);
	if (t_temp > 0 && t_temp < result->t_min)//how to treat t=0? when the intersection is on camera
	{
		process_square(object);
		if (check_sq_intersect(t_temp, object, dir, o) == 1)
		{
			result->t_min = t_temp;
			normalization(dir);
			vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);//store p vector
			vector_multi2(object->rgb, 1, result->rgb);//store rgb value
			update_normal(result->p, o, object->orientation, result->normal);
		}
	}
}

void	loop_obj(t_object *head, double o[3], double *pri_ray, t_result *result)
{
	while (head)
	{
		pri_ray = normalization(pri_ray);//when I multiply t, pri_ray got changed
		if((head->type[0] == 's' && head->type[1] == 'p') || (head->type[0] == 'p' && head->type[1] == 'l') || (head->type[0] == 't' && head->type[1] == 'r'))
			cal_intersect1(head, o, result, pri_ray);
		if (head->type[0] == 'c' && head->type[1] == 'y')
			cal_intersect2(head, o, result, pri_ray);
		if (head->type[0] == 's' && head->type[1] == 'q')
			cal_intersect3(head, o, result, pri_ray);
		head = head->next;
	}
}

int	check_light_intersect(t_light *light, t_result *result, t_object *object, t_setting *setting)
{
	//potentially loop through all the lights? update later
	double	*light_ray;
	// double	t_comp;
	t_result	result1;

	light_ray = malloc(3 * sizeof(double));
	if (!light_ray)
		return(0);//error message on memory allocation failure #updatelater
	result1.t_min = INFINITY;
	// printf("p is is %f %f %f\n", result->p[0], result->p[1], result->p[2]);
	vector_plus(result->p, vector_multi(result->normal, 1e-4), result->p);
	// printf("light rayx is is %f %f %f\n", light_ray[0], light_ray[1], light_ray[2]);
	vector_dir(light->coordinates, result->p, light_ray);
	// printf("light rayy is is %f %f %f\n", light_ray[0], light_ray[1], light_ray[2]);
	loop_obj(object, result->p, light_ray, &result1);
	// printf("light rayz is is %f %f %f\n", light_ray[0], light_ray[1], light_ray[2]);
	if (result1.t_min == INFINITY)
	{
		vector_multi(light_ray, -1);
		transfer_rgb(setting->rgb, result->ambient, setting->lighting_r[0]);
		cal_shade(result, light_ray);
		// printf("shade is %f\n", result->shade);
		transfer_rgb(light->rgb, result->diffuse, result->shade);
	}
	else
	{
		transfer_rgb(setting->rgb, result->ambient, setting->lighting_r[0]);//only ambient light applicable
		transfer_rgb(light->rgb, result->diffuse, 0);
	}
		// result->shade = 0;
	free(light_ray);
	return (1);
}

int		cal_return(t_object *objects, t_camera *camera, t_light *light, t_setting *setting)
{
	double	*pri_ray;
	t_object *head;
	int		color;
	t_result	result;


	pri_ray = malloc(3 * sizeof(double));
	if (!pri_ray)
		return (-1);//add check input NULL later
	head = objects;
	result.t_min = INFINITY;
	pri_ray = cast_ray(camera, setting->pix[0], setting->pix[1], pri_ray);
	// printf("ray is %f %f %f \n", pri_ray[0], pri_ray[1], pri_ray[2]);
	loop_obj(head, camera->coordinates, pri_ray, &result);//store p, rgb, normal
	// printf("p 0 is is %f %f %f\n", result.p[0], result.p[1], result.p[2]);
	// printf("result 1 t min is %f\n", result.t_min);
	if (result.t_min == INFINITY)
		color = create_trgb(0, 0, 0, 0);
	else
	{
		check_light_intersect(light, &result, head, setting);//calculate the shade value (loop throught the objects again to see if anything block the light)
		final_intensity(&result);
		color = cal_color(result.intensity, 0, result.rgb[0], result.rgb[1], result.rgb[2]);
		// printf("ambient is %f, %f %f\n", result.ambient[0], result.ambient[1], result.ambient[2]);
		// printf("difuse is %f, %f %f\n", result.diffuse[0], result.diffuse[1], result.diffuse[2]);
		// printf("result and color is %f, %f %f %d\n", result.intensity[0], result.intensity[1], result.intensity[2], color);
		// printf("color is %f, %f %f\n", result.rgb[0], result.rgb[1], result.rgb[2]);
		// color = add_shade(result.shade, 0, result.rgb[0], result.rgb[1], result.rgb[2]);//to adjust t value later, currently put into 0
	}
	free(pri_ray);
	return (color);
}

