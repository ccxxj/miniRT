/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/04 16:37:54 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/03/26 09:32:59 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int		check_newline(int n, char *str, char **line, t_store *store)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(*line);
	if (n == -1)
	{
		while (str[i])
		{
			(*line)[len + i] = str[i];
			i++;
		}
		free(store->rest_line);
		store->rest_line = NULL;
		return (1);
	}
	else
		return (0);
}

int		split(char **line, char *str, int n, t_store *store)
{
	int	i;
	int	len;

	len = ft_strlen(*line);
	if (!str)
		return (1);
	i = check_newline(n, str, line, store);
	if (i == 1)
		return (1);
	store->rest_line = ft_realloc(store->rest_line, ft_strlen(str) - n);
	if (!store->rest_line)
		return (-1);
	while (str[i])
	{
		if (i < n)
			(*line)[len + i] = str[i];
		if (i > n)
			store->rest_line[i - n - 1] = str[i];
		i++;
	}
	store->rest_line[i - n - 1] = '\0';
	return (1);
}

int		check_rest_line(char **line, char *str, int n, t_store *store)
{
	int	len;
	int	m;
	int	result;

	len = ft_strlen(*line);
	m = n == -1 ? ft_strlen(str) : n;
	*line = ft_realloc(*line, len + m + 1);
	if (!*line)
		return (-1);
	result = split(line, str, n, store);
	if (result == -1)
		return (-1);
	(*line)[len + m] = '\0';
	if (n > -1)
	{
		store->index_n = check_n(store->rest_line);
		return (1);
	}
	else
		return (0);
}

int		ft_read(int fd, char *buf, char **line, t_store *store)
{
	while (1)
	{
		store->result = read(fd, buf, BUFFER_SIZE);
		if (store->result == -1)
			return (-1);
		buf[store->result] = '\0';
		store->flag = store->result < BUFFER_SIZE ? 1 : 0;
		store->i = check_rest_line(line, buf, check_n(buf), store);
		if (check_n(buf) > -1)
			return (1);
		if ((store->flag == 1 && check_n(buf) < 0) || store->result == 0)
			return (0);
		if (check_n(buf) == -1)
			ft_bzero(buf, BUFFER_SIZE + 1);
	}
}

int		get_next_line(int fd, char **line)
{
	static	t_store	store;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!store.initialization)
	{
		store.rest_line = NULL;
		store.index_n = -1;
		store.flag = 0;
		store.initialization = 1;
		store.result = 0;
	}
	*line = (char *)malloc(10);
	if (!*line)
		return (-1);
	(*line)[0] = '\0';
	store.i = check_rest_line(line, store.rest_line, store.index_n, &store);
	if (store.i == -1)
		return (-1);
	if (store.flag == 1 && store.i == 0)
		return (0);
	if (store.i == 1)
		return (1);
	return (ft_read(fd, store.buf, line, &store));
}
