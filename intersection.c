/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 11:39:43 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/04/22 17:43:34 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//new function wrote
double cal_sp_intersect(double o[3], double c[3], double dir[3], float r)
{
	double	a;
	double	b;
	double	cc;
	double	q;
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
		//cal in loss of significance
		if (b > 0)
			q = - 0.5 * (b + sqrt(discriminant));
		else
			q = - 0.5 * (b - sqrt(discriminant));
		t1 = q / a;
		t2 = cc / q;
		free(co);
		if (t1 > t2)
			return (t2);
		else
			return (t1);
		// t1 = (-b + sqrt(discriminant)) / (2 * a); 
		// t2 = (-b - sqrt(discriminant)) / (2 * a);
		// free(co);
		// return (t2);//needto add the check if the object is behind camera, which both t1 t2 negative, no show
	}
}

double	cal_pl_intersect(double p0[3], double n[3], double dir[3], double o[3])
{
	double	t;
	double	product;
	double	*p0o;

	product = dot_product(dir, n);
	p0o = malloc(3 * sizeof(double));
	if (!p0o)
		return (-1);
	t = dot_product(vector_dir(p0, o, p0o), n) / product;
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
	// printf("dir coordi are %f %f %f \n", dir[0], dir[1], dir[2]);
	p = vector_plus(camera->coordinates, vector_multi(dir, t), p);
	// printf("p coordi are %f %f %f \n", p[0], p[1], p[2]);
	light_ray = normalization(vector_dir(p, light->coordinates, light_ray));
	// printf("light ray coordi are %f %f %f \n", light_ray[0], light_ray[1], light_ray[2]);
	if (object->type[0] == 's' && object->type[1] == 'p')
		normal = normalization(vector_dir(p, object->center, normal));//object center only works for sphere
	else//this is apply for pl and sq
	{
		normal[0] = object->orientation[0];
		normal[1] = object->orientation[1];
		normal[2] = object->orientation[2];
		normal = normalization(normal);
	}
	// printf("normal coordi are %f %f %f \n", normal[0], normal[1], normal[2]);
	shade = -dot_product(light_ray, normal);
	// printf("shade is %f \n", shade);
	free(light_ray);
	free(normal);
	free(p);
	if(shade < 0)//in the case light does not shine directly
		return (0);
	return (shade);
}

