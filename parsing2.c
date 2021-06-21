/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingredo2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 16:59:35 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/30 17:14:11 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialize_objects1(char *line, t_object **object)
{
	t_object	*new;
	char		**array;

	array = ft_split(line + 2, ' ', 3);
	create_object(&new);
	new->type[0] = line[0];
	new->type[1] = line[1];
	parse_elements(new->center, array[0], 3, 0);
	parse_elements(new->rgb, array[2], 3, 1);
	check_range(new->rgb, 0, 255, 3);
	if (line[0] == 's' && line[1] == 'p')
		parse_elements(new->diameter, array[1], 1, 0);
	if (line[0] == 'p' && line[1] == 'l')
	{
		parse_elements(new->orientation, array[1], 3, 0);
		check_normalization(new->orientation);
	}
	new->next = *object;
	*object = new;
	free_array(array, 3);
}

void	initialize_objects2(char *line, t_object **object)
{
	t_object	*new;
	char		**array;

	array = ft_split(line + 2, ' ', 4);
	create_object(&new);
	new->type[0] = line[0];
	new->type[1] = line[1];
	parse_elements(new->coordinates_1, array[0], 3, 0);
	parse_elements(new->orientation, array[1], 3, 0);
	check_normalization(new->orientation);
	parse_elements(new->lenth, array[2], 1, 0);
	parse_elements(new->rgb, array[3], 3, 1);
	check_range(new->rgb, 0, 255, 3);
	new->next = *object;
	*object = new;
	free_array(array, 4);
}

void	initialize_objects3(char *line, t_object **object)
{
	t_object	*new;
	char		**array;

	array = ft_split(line + 2, ' ', 5);
	create_object(&new);
	new->type[0] = line[0];
	new->type[1] = line[1];
	parse_elements(new->center, array[0], 3, 0);
	parse_elements(new->orientation, array[1], 3, 0);
	check_normalization(new->orientation);
	parse_elements(new->diameter, array[2], 1, 0);
	parse_elements(new->lenth, array[3], 1, 0);
	parse_elements(new->rgb, array[4], 3, 1);
	check_range(new->rgb, 0, 255, 3);
	new->next = *object;
	*object = new;
	free_array(array, 5);
}

void	initialize_objects4(char *line, t_object **object)
{
	t_object	*new;
	char		**array;

	array = ft_split(line + 2, ' ', 4);
	create_object(&new);
	new->type[0] = line[0];
	new->type[1] = line[1];
	parse_elements(new->coordinates_1, array[0], 3, 0);
	parse_elements(new->coordinates_2, array[1], 3, 0);
	parse_elements(new->coordinates_3, array[2], 3, 0);
	parse_elements(new->rgb, array[3], 3, 1);
	check_range(new->rgb, 0, 255, 3);
	vector_dir(new->coordinates_2, new->coordinates_1, new->tri_vect1);
	vector_dir(new->coordinates_3, new->coordinates_1, new->tri_vect2);
	cross_product(new->tri_vect1, new->tri_vect2, new->orientation);
	new->next = *object;
	*object = new;
	free_array(array, 5);
}
