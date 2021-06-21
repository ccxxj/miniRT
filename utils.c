/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/22 10:51:02 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:40:08 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_lstsize(t_camera *lst)
{
	t_camera	*head;
	int			count;

	if (!lst)
		return (0);
	count = 0;
	head = lst;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

double	dot_product(double a[3], double b[3])
{
	double	result;

	result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return (result);
}

double	*cross_product(double a[3], double b[3], double c[3])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
	return (c);
}

double	*matrix_mult(double a[4][4], double b[4], double c[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		c[i] = a[i][0] * b[0] + a[i][1] * b[1] + a[i][2] * b[2]
			+ a[i][3] * b[3];
		i++;
	}
	return (c);
}

void	create_vector(double **vector)
{
	*vector = malloc(3 * sizeof(double));
	if (!(*vector))
	{
		printf("Error\n %s", strerror(12));
		exit(0);
	}
}
