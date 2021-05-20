/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 11:39:43 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/10 19:49:31 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//this is to update the normal, stored in the object struct, where decide if the light will shine on the front or the backside
void	update_normal(double p[3], double o[3], double orientation[3], double normal[3])
{
	double *op;
	double dot_p;

	op = malloc(3 * sizeof(double));
	// if (!op)
	// 	return (-1);//update error message later #updatelater
	op = vector_dir(p, o, op);
	dot_p = dot_product(op, orientation);
	if (dot_p > 0)
		normal = vector_multi2(orientation, -1, normal);
	else
		normal = vector_multi2(orientation, 1, normal);
	normalization(normal);
}

//new function wrote
double cal_sp_intersect(double o[3], double c[3], double dir[3], double r)
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
		// printf("t1 is %f\n", t1);
		// printf("t2 is %f\n", t2);
		if (t1 > t2)//check later, need to deal with if 1 t is < 0 and another one bigger, inside of the object
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

double	cal_tr_intersect(t_object *object, double dir[3], double o[3])
{
	double	*pvec;
	double	*qvec;
	double	*ov0;
	double	epsilon;
	double	dot;
	double	u;
	double	v;
	double	t;
	double	det;

	epsilon = 0.000001;
	dot = dot_product(dir, object->orientation);
	if (dot > -epsilon && dot < epsilon)
		return (-1);//p out of trianle 
	pvec = malloc(3 * sizeof(double));
	if (!pvec)
		return (-1);
	qvec = malloc(3 * sizeof(double));
	if (!qvec)
		return (-1);
	ov0 = malloc(3 * sizeof(double));
	if (!ov0)
		return (-1);
	pvec = cross_product(dir, object->tri_vect2, pvec);
	ov0 = vector_dir(o, object->coordinates_1, ov0);//should be v0 to o
	det = dot_product(pvec, object->tri_vect1);
	u = dot_product(pvec, ov0) / det;
	if (u < 0 || u > 1)
	{
		free(pvec);
		free(qvec);
		free(ov0);
		return (-1);//p out of trianle 
	}
	qvec = cross_product(ov0, object->tri_vect1, qvec);
	v = dot_product(qvec, dir) / det;
	if (v < 0 || u + v > 1)
	{
		free(pvec);
		free(qvec);
		free(ov0);
		return (-1);//p out of trianle 
	}
	t = dot_product(qvec, object->tri_vect2) / det; //t should be >0 then this is in front of camera
	free(pvec);
	free(qvec);
	free(ov0);
	return (t);
}
