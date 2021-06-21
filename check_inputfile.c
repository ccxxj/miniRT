/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_inputfile.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 17:42:48 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/30 17:28:27 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minirt.h"

void	check_general_input(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ' || str[i] == 44 || str[i] == 46
			|| (str[i] > 47 && str[i]
				< 58) || (str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i]
				< 123) || str[i] == '-') && str[i])
		i++;
	if (str[i])
		print_error(3);
	i = 0;
	while (str[i])
	{
		if ((str[i] == ',' && str[i + 1] == ',')
			|| (str[i] == '.' && str[i + 1] == '.'))
			print_error(4);
		else
			i++;
	}
}

void	check_range(double *vec, int low, int high, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (vec[i] > high || vec[i] < low)
			print_error(5);
		else
			i++;
	}
}

void	check_float(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			print_error(4);
		i++;
	}
}

double	convert_nbr(char *str)
{
	t_parameters	d;

	initialize_parameters(&d);
	if (str[0] == '-')
	{
		d.neg = -1;
		d.i = 1;
	}
	while (str[d.i] && str[d.i] != ' ' && str[d.i] != ',' && str[d.i] != '.')
	{
		d.nb = d.nb * 10 + (str[d.i] - '0');
		d.i++;
	}
	if (str[d.i] == '.')
	{
		d.i++;
		while (str[d.i] && str[d.i] != ' ' && str[d.i] != ',')
		{
			d.nb = d.nb + (str[d.i] - '0') / pow(10, d.j);
			d.i++;
			d.j++;
		}
	}
	return (d.nb * d.neg);
}

void	check_normalization(double *vec)
{
	double	result;

	result = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	if (result != 1)
		print_error(6);
}
