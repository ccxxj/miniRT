/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/21 21:36:49 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 20:09:44 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cal_cameranb(int cameranb, int total)
{
	int	result;

	if (cameranb < 0)
		result = 0;
	else
		result = cameranb % total;
	return (result);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free_list(vars);
		exit(0);
	}
	if (keycode == 124)
	{
		vars->cameranb++;
		render(cal_cameranb(vars->cameranb, vars->listsize), vars);
	}
	if (keycode == 123)
	{
		vars->cameranb--;
		render(cal_cameranb(vars->cameranb, vars->listsize), vars);
	}
	return (0);
}

int	window_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free_list(vars);
	exit(0);
}

void	adjust_screensize(t_vars *vars)
{
	mlx_get_screen_size(vars->mlx, vars->sizex, vars->sizey);
	if (vars->setting.size[0] > vars->sizex[0])
		vars->setting.size[0] = vars->sizex[0];
	if (vars->setting.size[1] > vars->sizey[0])
		vars->setting.size[1] = vars->sizey[0];
}

void	minirt(int fd, int save)
{
	t_vars	vars;

	parse(fd, &vars);
	vars.cameranb = 0;
	vars.save = 0;
	adjust_screensize(&vars);
	if (save == 1)
	{
		create_buffer(&vars);
		render(0, &vars);
		free_buffer(&vars);
		return ;
	}
	vars.listsize = ft_lstsize(vars.camera);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.setting.size[0],
			vars.setting.size[1], "Hello world!");
	vars.img.img = mlx_new_image(vars.mlx, vars.setting.size[0],
			vars.setting.size[1]);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &(vars.img.bits_per_pixel),
			&(vars.img.line_length), &(vars.img.endian));
	render(0, &vars);
	mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, 17, 0, window_close, &vars);
	mlx_loop(vars.mlx);
}
