/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingredo.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 17:33:46 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/30 17:55:08 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialize_setting(char *line, t_setting *setting)
{
	char	**array;

	array = ft_split(line + 1, ' ', 2);
	if (line[0] == 'R')
	{
		parse_elements(&setting->size[0], array[0], 1, 1);
		parse_elements(&setting->size[1], array[1], 1, 1);
	}
	if (line[0] == 'A')
	{
		parse_elements(setting->lighting_r, array[0], 1, 0);
		parse_elements(setting->rgb, array[1], 3, 1);
		check_range(setting->lighting_r, 0, 1, 1);
		check_range(setting->rgb, 0, 255, 3);
	}
	free_array(array, 2);
}

void	initialize_camera(char *line, t_camera **camera)
{
	t_camera	*new;
	char		**array;

	array = ft_split(line + 1, ' ', 3);
	new = malloc(sizeof(t_camera));
	if (!new)
		print_error(2);
	parse_elements(new->coordinates, array[0], 3, 0);
	parse_elements(new->orientation, array[1], 3, 0);
	check_normalization(new->orientation);
	parse_elements(new->fov, array[2], 1, 0);
	check_range(new->fov, 0, 180, 1);
	new->next = *camera;
	*camera = new;
	free_array(array, 3);
}

void	initialize_light(char *line, t_light **light)
{
	t_light	*new;
	char	**array;

	array = ft_split(line + 1, ' ', 3);
	new = malloc(sizeof(t_light));
	if (!new)
		print_error(2);
	parse_elements(new->coordinates, array[0], 3, 0);
	parse_elements(new->brightness, array[1], 1, 0);
	check_range(new->brightness, 0, 1, 1);
	parse_elements(new->rgb, array[2], 3, 1);
	check_range(new->rgb, 0, 255, 3);
	new->next = *light;
	*light = new;
	free_array(array, 3);
}

void	parsing(char *line, t_vars *vars)
{
	check_general_input(line);
	if ((line[0] == 'R' || line[0] == 'A') && line[1] == ' ')
	{
		if (line[0] == 'R')
			vars->flag[0]++;
		else
			vars->flag[1]++;
		initialize_setting(line, &(vars->setting));
	}
	else if (line[0] == 'c' && line[1] == ' ')
		initialize_camera(line, &vars->camera);
	else if (line[0] == 'l' && line[1] == ' ')
		initialize_light(line, &vars->light);
	else if ((line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		|| (line[0] == 's' && line[1] == 'p' && line[2] == ' '))
		initialize_objects1(line, &vars->object);
	else if (line[0] == 's' && line[1] == 'q' && line[2] == ' ')
		initialize_objects2(line, &vars->object);
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		initialize_objects3(line, &vars->object);
	else if (line[0] == 't' && line[1] == 'r' && line[2] == ' ')
		initialize_objects4(line, &vars->object);
	else if (line[0])
		print_error(3);
}

void	parse(int fd, t_vars *vars)
{
	char	*line;
	int		result;

	vars->object = NULL;
	vars->light = NULL;
	vars->camera = NULL;
	initialize_flag(vars);
	while (1)
	{
		result = get_next_line(fd, &line);
		if (result == 1 || result == 0)
		{
			parsing(line, vars);
			free(line);
			if (result == 0)
				break ;
		}
		else
			print_error(2);
	}
	if (vars->flag[0] != 1 || vars->flag[1] > 1)
		print_error(8);
}
