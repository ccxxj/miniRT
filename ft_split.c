/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 17:30:28 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/30 17:07:35 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	int	str_len(char const *s, char c, int a)
{
	int		len;

	len = 0;
	while (s[a] != c && s[a] != '\0')
	{
		len++;
		a++;
	}
	return (len);
}

static	char	*fill_in(char *str, char const *s, int a, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		str[i] = s[a];
		i++;
		a++;
	}
	return (str);
}

static	char	**free_allo(char **array, int x)
{
	while (x > 0)
	{
		free(array[x - 1]);
		x--;
	}
	free(array);
	return (NULL);
}

static	char	**allocation(char **array, char const *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			array[x] = ft_calloc((str_len(s, c, i) + 1), sizeof(char));
			if (!array[x])
				return (free_allo(array, x));
			fill_in(array[x], s, i, str_len(s, c, i));
			x++;
		}
		i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c, int n)
{
	char	**array;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	if (count != n)
		print_error(1);
	array = ft_calloc(count + 1, sizeof(char *));
	if (!array)
		print_error(2);
	array[count] = NULL;
	return (allocation(array, s, c));
}
