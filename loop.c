/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/07 11:32:09 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/16 10:59:29 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cal_shade(t_result *result, double light_ray[3])
{
	normalization(result->normal);
	normalization(light_ray);
	result->shade = -dot_product(light_ray, result->normal);
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
	cal_top_intersect(object, dir, o);
	normalization(dir);
	cal_bottom_intersect(object, dir, o);
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
			// printf("p xx is is %f %f %f\n", result->p[0], result->p[1], result->p[2]);
			// printf("dir is is %f %f %f\n", dir[0], dir[1], dir[2]);
			// printf("tmin is %f\n", t_temp);
			normalization(dir);
			vector_plus(o, vector_multi2(dir, t_temp, result->p), result->p);//store p vector
			// printf("p jj is is %f %f %f\n", result->p[0], result->p[1], result->p[2]);
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

// int	check_light_intersect(t_light *light, t_result *result, t_object *object)
// {
// 	//potentially loop through all the lights? update later
// 	double	*light_ray;
// 	double	t_comp;
// 	t_result	result1;

// 	light_ray = malloc(3 * sizeof(double));
// 	if (!light_ray)
// 		return(0);//error message on memory allocation failure #updatelater
// 	result1.t_min = INFINITY;
// 	vector_dir(result->p, light->coordinates, light_ray);
// 	t_comp = sqrt(dot_product(light_ray, light_ray));//calculate the old t
// 	loop_obj(object, light->coordinates, light_ray, &result1);
// 	// vector_dir(result->p, light->coordinates, light_ray);
// 	// t_comp = sqrt(dot_product(light_ray, light_ray));//lengh = t value
// 	if ((result1.t_min - t_comp) < 0.000001 || (result1.t_min - t_comp) > -0.000001)//due to accuracy, have to keep the >= instead of =, somehow == does not work
// 	{
// 		cal_shade(result, light_ray);
// 	}
// 	else
// 		result->shade = 0;
// 	free(light_ray);
// 	return (1);
// }

int	check_light_intersect(t_light *light, t_result *result, t_object *object)
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
	vector_dir(light->coordinates, result->p, light_ray);
	loop_obj(object, result->p, light_ray, &result1);
	if (result1.t_min == INFINITY)
	{
		vector_multi(light_ray, -1);
		cal_shade(result, light_ray);
	}
	else
		result->shade = 0;
	free(light_ray);
	return (1);
}

int		cal_return(t_object *objects, t_camera *camera, t_light *light, int x, int y)
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
	pri_ray = cast_ray(camera, x, y, pri_ray);
	// printf("ray is %f %f %f \n", pri_ray[0], pri_ray[1], pri_ray[2]);
	loop_obj(head, camera->coordinates, pri_ray, &result);//store p, rgb, normal
	// printf("p 0 is is %f %f %f\n", result.p[0], result.p[1], result.p[2]);
	// printf("result 1 t min is %f\n", result.t_min);
	if (result.t_min == INFINITY)
		color = create_trgb(0, 0, 0, 0);
	else
	{
		check_light_intersect(light, &result, head);//calculate the shade value (loop throught the objects again to see if anything block the light)
		color = add_shade(result.shade, 0, result.rgb[0], result.rgb[1], result.rgb[2]);//to adjust t value later, currently put into 0
	}
	free(pri_ray);
	return (color);
}