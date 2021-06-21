/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buffer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/23 19:44:44 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:54:41 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	decode_color(int trgb, unsigned char buffer[3])
{
	buffer[2] = (unsigned char)((trgb & (0xFF << 16)) >> 16);
	buffer[1] = (unsigned char)((trgb & (0xFF << 8)) >> 8);
	buffer[0] = (unsigned char)(trgb & 0xFF);
}

void	create_buffer(t_vars *vars)
{
	int	i;

	vars->save = 1;
	i = 0;
	vars->buffer = (unsigned char **)malloc(vars->setting.size[0]
			* vars->setting.size[1] * sizeof(unsigned char *));
	if (!vars->buffer)
	{
		printf("Error\n %s", strerror(12));
		exit(0);
	}
	while (i < vars->setting.size[0] * vars->setting.size[1])
	{
		vars->buffer[i] = ft_calloc(3, sizeof(unsigned char));
		if (!vars->buffer)
		{
			printf("Error\n %s", strerror(12));
			exit(0);
		}
		i++;
	}
}

void	free_buffer(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->setting.size[0] * vars->setting.size[1])
	{
		free(vars->buffer[i]);
		i++;
	}
	free(vars->buffer);
	free_list(vars);
}
