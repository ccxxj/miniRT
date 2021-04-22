/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 14:18:42 by xxu           #+#    #+#                 */
/*   Updated: 2020/12/12 15:15:53 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	ft_bzero(void *str, size_t n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		((unsigned char *)str)[i] = '\0';
		i++;
		n--;
	}
}

int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

int		check_n(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_realloc(char *ptr, int size)
{
	char	*newptr;
	int		i;

	i = 0;
	if (!ptr)
	{
		ptr = (char *)malloc((size) * sizeof(char));
		return (ptr);
	}
	if (ft_strlen(ptr) >= size)
		return (ptr);
	newptr = (char *)malloc((size) * sizeof(char));
	while (ptr[i])
	{
		newptr[i] = ptr[i];
		i++;
	}
	newptr[i] = '\0';
	free(ptr);
	return (newptr);
}
