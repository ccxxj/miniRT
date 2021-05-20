/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/01 16:44:22 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/16 10:54:10 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//when the intersect happens on the side, it is to calculate the normal of the side point, normal is recorded in coordinate 3
void cy_normal(double *p, t_object *object)
{
	vector_dir(p, object->center, object->coordinates_1);//calculate the cp
	object->tri_vect1[0] = dot_product(object->coordinates_1, object->orientation);//calculate the projection of the cp, this can be check against the lenth
	vector_multi2(object->orientation, object->tri_vect1[0], object->coordinates_2);
	vector_dir(object->coordinates_1, object->coordinates_2, object->coordinates_3);
	normalization(object->coordinates_3);
}

double	cal_top_intersect(t_object *object, double dir[3], double o[3])
{
	double t;
	double *top;
	double *p;

	top = malloc(3 * sizeof(double));
	if (!top)
		return (-1);
	p = malloc(3 * sizeof(double));
	if (!p)
		return (-1);
	top = vector_plus(object->center, vector_multi(object->orientation, object->lenth[0] / 2), top);
	object->tri_vect2[0] = INFINITY;
	t = cal_pl_intersect(top, normalization(object->orientation), dir, o);
	if (t > 0)
	{
		p = vector_plus(o, vector_multi(dir, t), p);
		p = vector_dir(top, p, p);
		if (dot_product(p, p) <= object->diameter[0] * object->diameter[0])
			object->tri_vect2[0] = t;
		else
			object->tri_vect2[0] = INFINITY;//recorde the top t
	}
	normalization(object->orientation);
	return(0);
}

double	cal_bottom_intersect(t_object *object, double dir[3], double o[3])
{
	double t;
	double *bottom;
	double *p;

	bottom = malloc(3 * sizeof(double));
	if (!bottom)
		return (-1);
	p = malloc(3 * sizeof(double));
	if (!p)
		return (-1);
	bottom = vector_plus(object->center, vector_multi(object->orientation, -object->lenth[0] / 2), bottom);
	object->tri_vect2[1] = INFINITY;
	t = cal_pl_intersect(bottom, normalization(object->orientation), dir, o);
	if (t > 0)
	{
		p = vector_plus(o, vector_multi(dir, t), p);
		p = vector_dir(bottom, p, p);
		if (dot_product(p, p) <= object->diameter[0] * object->diameter[0])
			object->tri_vect2[1] = t;
		else
			object->tri_vect2[1] = INFINITY;//recorde the top t
	}
	normalization(object->orientation);
	return (0);
}

// rewrite check side value and return the right one
double	cal_discriminant(double *co, t_object *object, double *dir, double *o)
{
	double	dn;
	double	a;
	double	b;
	double	c;
	double	con;
	double	discriminant;

	// printf("dir is %f %f %f\n", dir[0], dir[1], dir[2]);
	// printf("orientation is %f %f %f\n", object->orientation[0], object->orientation[1], object->orientation[2]);
	// printf("center and diameter is %f %f %f %f\n", object->center[0], object->center[1], object->center[2], object->diameter[0]);

	dn = dot_product(dir, object->orientation);
	a = 1 - dn * dn;
	co = vector_dir(o, object->center, co);
	con = dot_product(co, object->orientation);
	b = 2 * dot_product(dir, co) - 2 * con * dn;
	c = dot_product(co, co) - object->diameter[0] * object->diameter[0] - con * con;
	discriminant = b * b - 4 * a * c;
	// printf("discribinant is %f\n", discriminant);
	co[0] = a;
	co[1] = b;
	co[2] = c;
	return (discriminant);
}

double	compare_t_value(t_object *object, double *t, double *dir, double *o)
{
	double *p;
	double dot_p;
	double result;

	p = malloc(3 * sizeof(double));
	//to update the error treatment later #update
	// if (!p)
	// 	Erroro message
	result = INFINITY;
	// printf("t 0 and t1 are %f %f \n", t[0], t[1]);
	if (t[0] > 0)
	{
		vector_plus(o, vector_multi2(dir, t[0], p), p);
		vector_dir(p, object->center, p);
		dot_p = dot_product(p, object->orientation);
		if (dot_p <= object->lenth[0] / 2 && dot_p >= -object->lenth[0] / 2 )
			result = t[0];
	}
	if (t[1] > 0)
	{
		vector_plus(o, vector_multi2(dir, t[1], p), p);
		vector_dir(p, object->center, p);
		dot_p = dot_product(p, object->orientation);
		if (dot_p <= object->lenth[0] / 2 && dot_p >= -object->lenth[0] / 2 && dot_p < result)
			result = t[1];
	}
	free(p);
	return (result);	
}

double	check_side(t_object *object, double *dir, double o[3])
{
	double	*co;
	double	discriminant;
	double	q;

	co = malloc(3 * sizeof(double));
	if (!co)
		return (0);
	discriminant = cal_discriminant(co, object, dir, o);
	// printf("discribinant is %f\n", discriminant);
	if (discriminant < 0)
	{
		free(co);
		return (0);
	}
	else
	{
		if (co[1] > 0)
			q = - 0.5 * (co[1] + sqrt(discriminant));
		else
			q = - 0.5 * (co[1] - sqrt(discriminant));
		co[0] = q / co[0];//record t1
		co[1] = co[2] / q;//record t2
		q = compare_t_value(object, co, dir, o);
		free(co);
		return (q);
	}
}