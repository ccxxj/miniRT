/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 12:59:25 by xxu           #+#    #+#                 */
/*   Updated: 2021/04/22 16:29:06 by xxu           ########   odam.nl         */
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

t_object *init_object()
{
	t_object *head;
	t_object *object;

	object = malloc(sizeof(t_object));
	object->type[0] = 's';
	object->type[1] = 'p';
	object->center[0] = 0;
	object->center[1] = 0;
	object->center[2] = 20;
	object->diameter[0] = 10;
	object->rgb[0] = 255;
	object->rgb[1] = 0;
	object->rgb[2] = 255;
	head = object;
	object = object->next;
	object = malloc(sizeof(t_object));
	object->type[0] = 's';
	object->type[1] = 'p';
	object->center[0] = -4;
	object->center[1] = 0;
	object->center[2] = 20;
	object->diameter[0] = 10;
	object->rgb[0] = 255;
	object->rgb[1] = 0;
	object->rgb[2] = 20;
	// head = object;
	object->next = NULL;
	return (head);
}


int	main(int argc, char **argv)
{
    void    *mlx;
    void    *mlx_win;
	t_data	img;
	int		a;
	int		b;
	int		color;
	int		fd;
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
		if (get_next_line(fd, &line) == 1)
			parsing(line, &setting, &camera, &light, &objects);
		else if (get_next_line(fd, &line) == 0)
		{
			parsing(line, &setting, &camera, &light, &objects);
			break;
		}
		else
			return (-1);//deal with erro message
	}

	// objects = init_object();
	// while(objects)
	// {
	// 	printf("object type rgb %s %f %f %f \n", objects->type, objects->rgb[0], objects->rgb[1], objects->rgb[2]);
	// 	objects = objects->next;
	// }
	// printf("width and heigh is %f %f \n", setting.size[0], setting.size[1]);
	// printf("ambient ratio is %f and the rbg are %f %f %f \n", setting.lighting_r[0], setting.rgb[0], setting.rgb[1], setting.rgb[2]);
	// printf("object type rgb %s %f %f %f \n", objects->type, objects->rgb[0], objects->rgb[1], objects->rgb[2]);
	// objects = objects->next;
	// if (objects->next != NULL)
		// printf("yes \n");
	// else
		// printf("no\n");
	// printf("object type rgb %s %f %f %f \n", objects->type, objects->rgb[0], objects->rgb[1], objects->rgb[2]);
	a = 0;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, setting.size[0], setting.size[1], "my first window");
    img.img = mlx_new_image(mlx, setting.size[0], setting.size[1]);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	// a = 500;
	// b = 500;
	// color = cal_return(objects, &setting, camera, light, a + 1, b + 1);
	// if (color == -1)
	// 	return (-1);
	// my_mlx_pixel_put(&img, a, b, color);
	
	
	
	
	while (a < setting.size[0])
	{
		b = 0;
		while (b < setting.size[1])
		{
			color = cal_return(objects, &setting, camera, light, a + 1, b + 1);
			if (color == -1)//this is the problem when my window gets bigger, the return is -1
				return (-1);                   
			my_mlx_pixel_put(&img, a, b, color);
			b++;
		}
		a++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}


//this is to add to test specific spot 
	// a = 500;
	// b = 500;
	// color = cal_return(objects, &setting, &camera, &light, a + 1, b + 1);
	// if (color == -1)
	// 	return (-1);
	// my_mlx_pixel_put(&img, a, b, color);

