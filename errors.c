/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xxu <xxu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 12:47:14 by xxu           #+#    #+#                 */
/*   Updated: 2021/05/28 18:20:16 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minirt.h"

void	print_error(int a)
{
	if (a == 1)
		printf("Error\n the number of elements of input information incorrect");
	if (a == 2)
		printf("Error\n %s", strerror(12));
	if (a == 3)
		printf("Error\n forbidden character appear in the configuration file");
	if (a == 4)
		printf("Error\n incorrect format in configuration file");
	if (a == 5)
		printf("Error\n input exeeding normal range in configuration file");
	if (a == 6)
		printf("Error\n orientation vector is not normalized");
	if (a == 7)
		printf("Error\n %s", strerror(12));
	if (a == 8)
		printf("Error\n too many or too less R and A input");
	exit(0);
}
