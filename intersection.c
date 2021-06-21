/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 11:39:43 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/27 15:19:22 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*this is to update the normal, stored in the object struct, 
where decide if the light will shine on the front or the backside */
void	update_normal(double p[3], double o[3], double orientation[3],
	double normal[3])
{
	double	*op;
	double	dot_p;

	op = malloc(3 * sizeof(double));
	if (!op)
	{
		printf("error : %s\n", strerror(12));
		exit(0);
	}
	op = vector_dir(p, o, op);
	dot_p = dot_product(op, orientation);
	if (dot_p > 0)
		normal = vector_multi2(orientation, -1, normal);
	else
		normal = vector_multi2(orientation, 1, normal);
	normalization(normal);
	free(op);
}

double	sp_intersect(double a, double b, double cc, double discriminant)
{
	double	t1;
	double	t2;
	double	q;

	discriminant = b * b - 4 * a * cc;
	if (discriminant < 0)
		return (-1);
	else
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discriminant));
		else
			q = -0.5 * (b - sqrt(discriminant));
		t1 = q / a;
		t2 = cc / q;
		if ((t1 > t2 && t1 * t2 > 0) || (t2 > t1 && t1 * t2 <= 0))
			return (t2);
		else
			return (t1);
	}
}

double	cal_sp_intersect(double o[3], double c[3], double dir[3], double r)
{
	double	a;
	double	b;
	double	cc;
	double	discriminant;
	double	*co;

	a = 1;
	create_vector(&co);
	co = vector_dir (o, c, co);
	b = 2 * dot_product(co, dir);
	cc = dot_product(co, co) - r * r;
	discriminant = b * b - 4 * a * cc;
	a = sp_intersect(a, b, cc, discriminant);
	free(co);
	return (a);
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
	{
		free(p0o);
		return (t);
	}
	else
	{
		free(p0o);
		return (-1);
	}
}

double	cal_tr_intersect(t_object *object, double dir[3], double o[3])
{
	double		u;
	double		v;
	double		t;
	double		det;
	t_triangle	tri;

	det = dot_product(dir, object->orientation);
	if (det > -0.000001 && det < 0.000001)
		return (-1);
	cross_product(dir, object->tri_vect2, tri.pvec);
	vector_dir(o, object->coordinates_1, tri.ov0);
	det = dot_product(tri.pvec, object->tri_vect1);
	u = dot_product(tri.pvec, tri.ov0) / det;
	if (u < 0 || u > 1)
		return (-1);
	cross_product(tri.ov0, object->tri_vect1, tri.qvec);
	v = dot_product(tri.qvec, dir) / det;
	if (v < 0 || u + v > 1)
		return (-1);
	t = dot_product(tri.qvec, object->tri_vect2) / det;
	return (t);
}
