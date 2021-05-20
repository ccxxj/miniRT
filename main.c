/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:59:25 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/16 10:54:29 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "minirt.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		add_shade(double a, int t, int r, int g, int b)
{
	t = a * t;
	r = a * r;
	g = a * g;
	b = a * b;
	return (create_trgb(t, r, g, b));
}

// int	close(int keycode, t_vars *vars)
// {
// 	mlx_destroy_window(vars->mlx, vars->win);
// }

int	main(int argc, char **argv)
{
    // void    *mlx;
    // void    *mlx_win;
	t_vars	vars;
	t_data	img;
	int		a;
	int		b;
	int		color;
	int		fd;
	int		result;
	char	*line;
	t_setting	setting;//setting can only be one
	t_camera	*camera;//deal with multiple camera later, for now stay struct instead of list
	t_object	*objects;
	t_light		*light;//deal with multiple lights later, for now stay struct instead of list

// data parsing
	if (argc < 2)
		return (-1); //error handling to update later
	fd = open(argv[1], O_RDONLY);
	objects = NULL;
	while (1)
	{
		result = get_next_line(fd, &line);
		if (result == 1)
		{
			parsing(line, &setting, &camera, &light, &objects);
			free(line);
		}
		else if (result == 0)
		{
			parsing(line, &setting, &camera, &light, &objects);
			free(line);
			break;
		}
		else
			return (-1);
	}
	a = 0;
	camera_set(camera, &setting);
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, setting.size[0], setting.size[1], "my first window");
    img.img = mlx_new_image(vars.mlx, setting.size[0], setting.size[1]);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// a = 249;
	// b = 249;
	// color = cal_return(objects, camera, light, a + 1, b + 1);
	// if (color == -1)
	// 	return (-1);
	// my_mlx_pixel_put(&img, a, b, color);
	
	while (a < setting.size[0])
	{
		b = 0;
		while (b < setting.size[1])
		{
			// color = cal_return(objects, &setting, camera, light, a + 1, b + 1);
			color = cal_return(objects, camera, light, a, setting.size[1] - b);
			if (color == -1)//this is the problem when my window gets bigger, the return is -1
				return (-1);                   
			my_mlx_pixel_put(&img, a, b, color);
			b++;
		}
		a++;
	}
	
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}
