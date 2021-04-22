/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera_matrix.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/15 13:45:33 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/04/22 16:29:42 by xxu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//return the primary ray
// double	*pix_camera(int w, int h, double FOV, int x, int y)
double	*pix_camera(double w, double h, double FOV, double x, double y, double *pri_ray)
{
	double	Px;
	double	Py;

	Px = ((2 * x - 1) / w - 1) * tan(FOV / 2 * M_PI / 180);
	double tang = tan(FOV / 2 * M_PI / 180);
	double py1 = (h + 1 - 2 * y) / w;
	Py = py1 * tang;
	pri_ray[0] = Px;
	pri_ray[1] = Py;
	
	pri_ray[2] = 1; // is this 1 or -1?? check later
	return (pri_ray);

	//return the transformed ray
}

int		cal_return(t_object *objects, t_setting *setting, t_camera *camera, t_light *light, int x, int y)
{
	double	*pri_ray;
	t_object *head;
	double	t_min;
	double	t_temp;
	double	shade;
	int		r;
	int		g;
	int		b;
	int		color;

	head = objects;
	// t_object *head;
	// head = objects;
	// while (head)
	// {
	// 	printf("obj isssss %s\n", objects->type);
	// 	head = head->next;
	// }
	pri_ray = malloc(3 * sizeof(double));
	if (!pri_ray)
		return (-1);//add check input NULL later
	pri_ray = pix_camera(setting->size[0], setting->size[1], camera->fov[0], x, y, pri_ray);
	t_min = INFINITY;
	while (head)
	{
		//check all sphere objects
		pri_ray = normalization(pri_ray);//when I multiply t, pri_ray got changed
		// printf("check 1\n");
		// if (objects->type[0] == 's' && objects->type[1] == 'p')
		if (head->type[0] == 's' && head->type[1] == 'p')
		{
			// printf("check 2\n");
			t_temp = cal_sp_intersect(camera->coordinates, head->center, pri_ray, head->diameter[0]);
			// printf("t temp is %f\n", t_temp);
			if (t_temp > 0 && t_temp < t_min)//how to treat t=0? when the intersection is on camera
			{
				shade = cal_shade(t_temp, camera, head, pri_ray, light);
				if (shade != -1)
				{
					t_min = t_temp;
					r = head->rgb[0];
					g = head->rgb[1];
					b = head->rgb[2];
				}
				else
				{
					free(pri_ray);
					return (-1);
				}
			}
		}
		if (head->type[0] == 'p' && head->type[1] == 'l')//TO TEST TMR ABOUT PLANE!!!
		{
			// printf("check 3\n");
			t_temp = cal_pl_intersect(head->center, head->orientation, pri_ray, camera->coordinates);
			// printf("t temp is %f\n", t_temp);
			if (t_temp > 0 && t_temp < t_min)//how to treat t=0? when the intersection is on camera
			{
				shade = cal_shade(t_temp, camera, head, pri_ray, light);
				// printf("shade is %f\n", shade);
				if (shade != -1)
				{
					t_min = t_temp;
					r = head->rgb[0];
					g = head->rgb[1];
					b = head->rgb[2];
				}
				else
				{
					free(pri_ray);
					return (-1);
				}
			}
		}
		head = head->next;
	}
	if (t_min == INFINITY)
		color = create_trgb(0, 0, 0, 0);
	else
		color = add_shade(shade, 0, r, g, b);//to adjust t value later, currently put into 0
	free(pri_ray);
	return (color);
//add ambient lighting
}
