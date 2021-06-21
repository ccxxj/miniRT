/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/27 14:53:39 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/30 17:05:01 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstclear_object(t_object **lst)
{
	t_object	*head;
	t_object	*next;

	head = *lst;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
	*lst = NULL;
}

void	ft_lstclear_camera(t_camera **lst)
{
	t_camera	*head;
	t_camera	*next;

	head = *lst;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
	*lst = NULL;
}

void	ft_lstclear_light(t_light **lst)
{
	t_light	*head;
	t_light	*next;

	head = *lst;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
	*lst = NULL;
}

void	free_list(t_vars *vars)
{
	ft_lstclear_object(&vars->object);
	ft_lstclear_light(&vars->light);
	ft_lstclear_camera(&vars->camera);
}
