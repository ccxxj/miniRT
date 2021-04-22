/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 09:58:38 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/04/22 10:08:02 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minirt.h"

/*
to deal tmr:
missing cylinder line
check how to deal with mulitiple /n
check if it works with mulitple same objects, cameras, lights
*/


//adjust, take in also minus number, as well as where to place the output
double	parse_number(char *str, double *nbr, int a)
{
	int i;
	int j;
	double nb;
	int neg;

	i = 0;
	j = 1;
	nb = 0;
	neg = 1;
	if (str[0] == '-')
	{
		neg = -1;
		i = 1;
	}
	while (str[i] && str[i] != ' ' && str[i] != ',' && str[i] != '.')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] && str[i] != ' ' && str[i] != ',')
		{
			nb = nb + (str[i] - '0') / pow(10, j);
			i++;
			j++;
		}
	}
	nbr[a] = nb * neg;
	return (i);
}

char *parse_line(char *line, double *a, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < n)
	{
		while (line[j])
		{
			if (line[j] == ' ')
				j++;
			else
			{
				if (line[j] == '-' || (line[j] < 58 && line[j] > 47))
				{
					j = j + parse_number (line + j, a, i);
					break;
				}
				else
					j++;
			}
		}
		i++;
	}
	return (line + j);
}

void	initialize_setting(char *line, t_setting *setting)
{
	int i;

	i = 0;
	if (line[0] == 'R')
	{
		parse_line(line + 1, setting->size, 2);
	}
	if (line[0] == 'A')
	{
		line = parse_line(line + 1, setting->lighting_r, 1);
		parse_line(line, setting->rgb, 3);
	}
}

void	*initialize_objects(char *line, t_object **object)
{
	t_object *new;

	new = malloc(sizeof(t_object));//remember to free the space at the end
	if (!new)
		return NULL;//add to error reporting later
	new->type[0] = line[0];
	new->type[1] = line[1];
	if (line[0] == 's' && line[1] == 'p')
	{
		line = parse_line(line + 2, new->center, 3);
		line = parse_line(line, new->diameter, 1);
		parse_line(line, new->rgb, 3);
	}
	if (line[0] == 'p' && line[1] == 'l')
	{
		// line = parse_line(line + 2, new->coordinates_1, 3);
		line = parse_line(line + 2, new->center, 3);
		line = parse_line(line, new->orientation, 3);
		parse_line(line, new->rgb, 3);
	}
	if (line[0] == 's' && line[1] == 'q')
	{
		line = parse_line(line + 2, new->coordinates_1, 3);
		line = parse_line(line, new->orientation, 3);
		line = parse_line(line, new->lenth, 1);
		parse_line(line, new->rgb, 3);
	}
	if (line[0] == 'c' && line[1] == 'y')
	{
		line = parse_line(line + 2, new->coordinates_1, 3);
		line = parse_line(line, new->orientation, 3);
		line = parse_line(line, new->diameter, 1);
		line = parse_line(line, new->lenth, 1);
		parse_line(line, new->rgb, 3);
	}
	if (line[0] == 't' && line[1] == 'r')
	{
		line = parse_line(line + 2, new->coordinates_1, 3);
		line = parse_line(line, new->coordinates_2, 3);
		line = parse_line(line, new->coordinates_3, 3);
		parse_line(line, new->rgb, 3);
	}
	new->next = *object;
	*object = new;
	return (*object);
}

void	*initialize_light(char *line, t_light **light)
{
	t_light *new;

	new = malloc(sizeof(t_light));
	if (!new)
		return NULL;//add to error reporting later
	line = parse_line(line + 1, new->coordinates, 3);
	line = parse_line(line, new->brightness, 1);
	parse_line(line, new->rgb, 3);
	new->next = *light;
	*light = new;
	return (*light);
}

void	*initialize_camera(char *line, t_camera **camera)
{
	t_camera *new;

	new = malloc(sizeof(t_camera));
	if (!new)
		return NULL;//add to error reporting later
	line = parse_line(line + 1, new->coordinates, 3);
	line = parse_line(line, new->orientation, 3);
	parse_line(line, new->fov, 1);
	new->next = *camera;
	*camera = new;
	return (*camera);
}


void	parsing(char *line, t_setting *setting, t_camera **camera, t_light **light, t_object **object)
{
	if(line[0] == 'R' || line[0] == 'A')
		initialize_setting(line, setting);
	else if (line[0] == 'c' && line[1] != 'y')
		initialize_camera(line, camera);
	else if (line[0] == 'l')
		initialize_light(line, light);
	else if ((line[0] == 'p' && line[1] == 'l') || (line[0] == 's' && line[1] == 'p')
	|| (line[0] == 's' && line[1] == 'q') || (line[0] == 'c' && line[1] == 'y') ||
	(line[0] == 't' && line[1] == 'r'))
		initialize_objects(line, object);
}

// int main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	//later move the initialize structs to the int main function 
// 	t_setting	setting;//setting can only be one
// 	t_camera	*camera;//deal with multiple camera later, for now stay struct instead of list
// 	t_light		*light;
// 	t_object	*objects;
	
// 	if (argc < 2)
// 		return (-1); //error handling to update later
	
// 	fd = open(argv[1], O_RDONLY);
// 	while (1)
// 	{
// 		if (get_next_line(fd, &line) == 1)
// 			parsing(line, &setting, &camera, &light, &objects);
// 		else if (get_next_line(fd, &line) == 0)
// 		{
// 			parsing(line, &setting, &camera, &light, &objects);
// 			break;
// 		}
// 		else
// 			return (-1);//deal with erro message
// 	}
// 	// printf("width and heigh is %f %f \n", setting.size[0], setting.size[1]);
// 	// printf("ambient ratio is %f and the rbg are %f %f %f \n", setting.lighting_r[0], setting.rgb[0], setting.rgb[1], setting.rgb[2]);
// 	while (objects)
// 	{
// 		// printf("object type rgb %s %f %f %f \n", objects->type, objects->rgb[0], objects->rgb[1], objects->rgb[2]);
// 		objects = objects->next;
// 	}
// 	// printf("camear coor, orientation and fov are %f %f %f %f %f %f %f\n", camera->coordinates[0], camera->coordinates[1], camera->coordinates[2], camera->orientation[0], camera->orientation[1], camera->orientation[2], camera->fov[0]);
// 	// printf("light coor, rgb and brightness are %f %f %f %f %f %f %f\n", light->coordinates[0], light->coordinates[1], light->coordinates[2], setting.rgb[0], setting.rgb[1], setting.rgb[2], light->brightness[0]);
// }


// int main()
// {
// 	// double a[3];
// 	// char *line;
// 	// t_setting setting;
// 	t_object *object;

// 	object = NULL;
// 	// initialize_setting("R   1560 123123   ddd", &setting);
// 	// printf("width and heigh is %f %f \n", setting.size[0], setting.size[1]);
// 	// initialize_setting("A   6.5  255,255,255", &setting);
// 	// printf("ambient ratio is %f and the rbg are %f %f %f \n", setting.lighting_r[0], setting.rgb[0], setting.rgb[1], setting.rgb[2]);
// 	object = initialize_objects("sp  1,1,20     30     255,255,255   1", &object);
// 	object = initialize_objects("sp  0,1.555,20     30.6     0,255,255   1", &object);
// 	printf("object type coordination diameter and rgb %s %f %f %f %f %f %f %f \n", object->type, object->diameter[0], object->center[0], object->center[1], object->center[2], object->rgb[0], object->rgb[1], object->rgb[2]);
// 	object = object->next;
// 	printf("object type coordination diameter and rgb %s %f %f %f %f %f %f %f \n", object->type, object->diameter[0], object->center[0], object->center[1], object->center[2], object->rgb[0], object->rgb[1], object->rgb[2]);
// }