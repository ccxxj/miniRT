/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/21 21:15:41 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:54:56 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;
	int	len;

	len = ft_strlen(str1);
	if (len != n)
		return (1);
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_rtfile(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 2] == 'r' && str[len - 1] == 't' && str[len - 3] == '.')
		return (0);
	else
		return (1);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac < 2 || ac > 3)
	{
		printf("Error\n %s", strerror(5));
		return (0);
	}
	else
	{
		if (check_rtfile(av[1]) == 1)
		{
			printf("Error\n %s", strerror(79));
			return (0);
		}
		fd = open(av[1], O_RDONLY);
		if (ac == 2)
			minirt(fd, 0);
		else if (ft_strncmp(av[2], "--save", 6) == 0)
		{
			minirt(fd, 1);
		}
	}
	close (fd);
	return (0);
}
