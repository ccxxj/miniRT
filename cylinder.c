/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/01 16:44:22 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/24 14:53:16 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	cal_top_intersect(t_object *object, double dir[3], double o[3])
{
	double	t;
	double	*top;
	double	*p;

	top = NULL;
	p = NULL;
	create_vector(&top);
	create_vector(&p);
	top = vector_plus(object->center, vector_multi(object->orientation,
				object->lenth[0] / 2), top);
	object->tri_vect2[0] = INFINITY;
	t = cal_pl_intersect(top, normalization(object->orientation), dir, o);
	if (t > 0)
	{
		p = vector_plus(o, vector_multi2(dir, t, p), p);
		p = vector_dir(top, p, p);
		if (dot_product(p, p) <= object->diameter[0] * object->diameter[0])
			object->tri_vect2[0] = t;
		else
			object->tri_vect2[0] = INFINITY;
	}
	normalization(object->orientation);
	free(top);
	free(p);
	return (0);
}

double	cal_bottom_intersect(t_object *object, double dir[3], double o[3])
{
	double	t;
	double	*bottom;
	double	*p;

	bottom = NULL;
	p = NULL;
	create_vector(&bottom);
	create_vector(&p);
	bottom = vector_plus(object->center, vector_multi(object->orientation,
				-object->lenth[0] / 2), bottom);
	object->tri_vect2[1] = INFINITY;
	t = cal_pl_intersect(bottom, normalization(object->orientation), dir, o);
	if (t > 0)
	{
		p = vector_plus(o, vector_multi2(dir, t, p), p);
		p = vector_dir(bottom, p, p);
		if (dot_product(p, p) <= object->diameter[0] * object->diameter[0])
			object->tri_vect2[1] = t;
		else
			object->tri_vect2[1] = INFINITY;
	}
	normalization(object->orientation);
	free(bottom);
	free(p);
	return (0);
}

double	cal_discriminant(double *co, t_object *object, double *dir, double *o)
{
	double	a;
	double	b;
	double	c;
	double	con;
	double	discriminant;

	a = 1 - dot_product(dir, object->orientation) * dot_product(dir,
			object->orientation);
	co = vector_dir(o, object->center, co);
	con = dot_product(co, object->orientation);
	b = 2 * dot_product(dir, co) - 2 * con * dot_product(dir,
			object->orientation);
	c = dot_product(co, co) - object->diameter[0] * object->diameter[0]
		- con * con;
	discriminant = b * b - 4 * a * c;
	co[0] = a;
	co[1] = b;
	co[2] = c;
	return (discriminant);
}

double	compare_t_value(t_object *object, double *t, double *dir, double *o)
{
	double	*p;
	double	dot_p;
	double	result;

	create_vector(&p);
	result = INFINITY;
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
		if (dot_p <= object->lenth[0] / 2 && dot_p >= -object->lenth[0] / 2
			&& dot_p < result)
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

	co = NULL;
	create_vector(&co);
	discriminant = cal_discriminant(co, object, dir, o);
	if (discriminant < 0)
	{
		free(co);
		return (0);
	}
	else
	{
		if (co[1] > 0)
			q = -0.5 * (co[1] + sqrt(discriminant));
		else
			q = -0.5 * (co[1] - sqrt(discriminant));
		co[0] = q / co[0];
		co[1] = co[2] / q;
		q = compare_t_value(object, co, dir, o);
		free(co);
		return (q);
	}
}
