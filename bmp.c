/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/23 13:19:08 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/27 11:52:29 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	printfileheader(int fd, int height, int stride)
{
	int						filesize;
	static unsigned char	fileheader[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0};

	filesize = 54 + (stride * height);
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(filesize);
	fileheader[3] = (unsigned char)(filesize >> 8);
	fileheader[4] = (unsigned char)(filesize >> 16);
	fileheader[5] = (unsigned char)(filesize >> 24);
	fileheader[10] = (unsigned char)(54);
	write(fd, fileheader, 14);
}

void	printinfoheader(int fd, int height, int width)
{
	static unsigned char	infoheader[] = {0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0};

	infoheader[0] = (unsigned char)(40);
	infoheader[4] = (unsigned char)(width);
	infoheader[5] = (unsigned char)(width >> 8);
	infoheader[6] = (unsigned char)(width >> 16);
	infoheader[7] = (unsigned char)(width >> 24);
	infoheader[8] = (unsigned char)(height);
	infoheader[9] = (unsigned char)(height >> 8);
	infoheader[10] = (unsigned char)(height >> 16);
	infoheader[11] = (unsigned char)(height >> 24);
	infoheader[12] = (unsigned char)(1);
	infoheader[14] = (unsigned char)(24);
	write(fd, infoheader, 40);
}

void	print_body(t_vars *vars, int fd, int pad_size)
{
	int						i;
	int						j;
	static unsigned char	padding[] = {0, 0, 0};

	i = vars->setting.size[1] - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < vars->setting.size[0])
		{
			write(fd, vars->buffer[i * (int)(vars->setting.size[0]) + j], 3);
			j++;
		}
		j = 0;
		while (j < pad_size)
		{
			write(fd, padding, 1);
			j++;
		}
		i--;
	}
}

void	write_bmp(t_vars *vars)
{
	int	width_bytes;
	int	pad_size;
	int	stride;
	int	fd;

	width_bytes = vars->setting.size[0] * 3;
	pad_size = (4 - (width_bytes) % 4) % 4;
	stride = width_bytes + pad_size;
	fd = open("img.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!fd)
		printf("Error\n %s", strerror(2));
	printfileheader(fd, vars->setting.size[1], stride);
	printinfoheader(fd, vars->setting.size[1], vars->setting.size[0]);
	print_body(vars, fd, pad_size);
	close(fd);
}
