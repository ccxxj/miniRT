/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/21 23:43:10 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:53:02 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_camera	*match_camera(int cameranb, t_camera *camera)
{
	t_camera	*head;
	int			i;

	head = camera;
	i = 0;
	while (i < cameranb)
	{
		head = head->next;
		i++;
	}
	return (head);
}

void	render_exec(t_camera *camera, t_vars *vars)
{
	int	a;
	int	b;
	int	color;

	a = 0;
	while (a < vars->setting.size[0])
	{
		b = 0;
		while (b < vars->setting.size[1])
		{
			vars->setting.pix[0] = a;
			vars->setting.pix[1] = vars->setting.size[1] - b;
			color = cal_return(vars->object, camera, vars->light,
					&(vars->setting));
			if (vars->save == 1)
				decode_color(color, vars->buffer[b * ((int)
						(vars->setting.size[0])) + a]);
			else
				my_mlx_pixel_put(&(vars->img), a, b, color);
			b++;
		}
		a++;
	}
}

void	render(int cameranb, t_vars *vars)
{
	t_camera	*camera_n;

	if (vars->object)
	{
		camera_n = match_camera(cameranb, vars->camera);
		camera_set(camera_n, &vars->setting);
		render_exec(camera_n, vars);
		if (vars->save == 1)
			write_bmp(vars);
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	}
	else
	{
		if (vars->save == 1)
			write_bmp(vars);
	}
}
