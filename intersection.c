/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 11:39:43 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/04/22 09:55:45 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//new function wrote
double cal_sp_intersect(double o[3], double c[3], double dir[3], float r)
{
	double	a;
	double	b;
	double	cc;
	double	discriminant;
	double	t1;
	double	t2;
	double	*co;

	a = 1;
	co = malloc(3 * sizeof(double));
	if (!co)
		return (0);
	co = vector_dir (o, c, co);
	b = 2 * dot_product(co, dir);
	cc = dot_product(co, co) - r * r;
	discriminant = b * b - 4 * a * cc;
	if (discriminant < 0)
	{
		free(co);
		return (-1);
	}
	else
	{
		t1 = (-b + sqrt(discriminant)) / (2 * a); 
		t2 = (-b - sqrt(discriminant)) / (2 * a);
		free(co);
		return (t2);//needto add the check if the object is behind camera, which both t1 t2 negative, no show
	}
}

double	cal_pl_intersect(double p0[3], double n[3], double dir[3], double o[3])
{
	double	t;
	double	product;
	double	*p0o;

	product = dot_product(dir, n);
	p0o = malloc(3 * sizeof(double));
	t = dot_product(vector_dir(p0, o, p0o), n);
	if (t >= 0)
		return (t);
	else
		return (-1);
}

double cal_shade(double t, t_camera *camera, t_object *object, double *dir, t_light *light)
{
	double	shade;
	double	*p;
	double	*normal;
	double	*light_ray;

	light_ray = malloc(3 * sizeof(double));
	if (!light_ray)
		return (-1);
	normal = malloc(3 * sizeof(double));
	if (!normal)
		return (-1);
	p = malloc(3 * sizeof(double));
	if (!p)
		return (-1);
	p = vector_plus(camera->coordinates, vector_multi(dir, t), p);
	light_ray = normalization(vector_dir(p, light->coordinates, light_ray));
	normal = normalization(vector_dir(p, object->center, normal));//object center only works for sphere
	shade = -dot_product(light_ray, normal);
	if(shade < 0)//in the case light does not shine directly
		return (0);
	free(light_ray);
	free(normal);
	free(p);
	return (shade);
}

