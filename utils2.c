/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 13:46:44 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/28 18:43:44 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialize_parameters(t_parameters *d)
{
	d->i = 0;
	d->nb = 0;
	d->j = 1;
	d->neg = 1;
}

void	create_object(t_object	**object)
{
	*object = malloc(3 * sizeof(t_object));
	if (!(*object))
		print_error(2);
}

void	free_array(char **array, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	parse_elements(double *dest, char *str, int nb, int bool)
{
	int		i;
	char	**array2;

	i = 0;
	if (bool == 1)
		check_float(str);
	if (nb > 1)
	{
		array2 = ft_split(str, ',', nb);
		while (i < nb)
		{
			dest[i] = convert_nbr(array2[i]);
			i++;
		}
		free_array(array2, nb);
	}
	else
		dest[i] = convert_nbr(str);
}

void	initialize_flag(t_vars *vars)
{
	vars->flag[0] = 0;
	vars->flag[1] = 0;
}
