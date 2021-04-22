/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 14:35:10 by xxu           #+#    #+#                 */
/*   Updated: 2020/12/12 15:12:39 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

typedef struct		s_list
{
	char	*rest_line;
	char	buf[BUFFER_SIZE + 1];
	int		index_n;
	int		flag;
	int		i;
	int		result;
	int		initialization;
}					t_store;

void				ft_bzero(void *str, size_t n);
int					ft_strlen(const char *s);
int					get_next_line(int fd, char **line);
int					check_n(char *str);
char				*ft_realloc(char *ptr, int size);

#endif
