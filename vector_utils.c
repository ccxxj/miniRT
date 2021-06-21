/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/15 13:44:36 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/24 02:05:17 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*vector_dir(double a[3], double b[3], double ba[3])
{
	ba[0] = a[0] - b[0];
	ba[1] = a[1] - b[1];
	ba[2] = a[2] - b[2];
	return (ba);
}

double	*vector_plus(double a[3], double b[3], double ab[3])
{
	ab[0] = a[0] + b[0];
	ab[1] = a[1] + b[1];
	ab[2] = a[2] + b[2];
	return (ab);
}

double	*vector_multi(double a[3], double b)
{
	a[0] = a[0] * b;
	a[1] = a[1] * b;
	a[2] = a[2] * b;
	return (a);
}

double	*vector_multi2(double a[3], double b, double c[3])
{
	c[0] = a[0] * b;
	c[1] = a[1] * b;
	c[2] = a[2] * b;
	return (c);
}

double	*normalization(double *a)
{
	double	square;

	square = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / square;
	a[1] = a[1] / square;
	a[2] = a[2] / square;
	return (a);
}
