#include "minirt.h"

#include <stdio.h>
#include <mlx.h>

// void parsing(int *str)
// {
// 	str[0] = 133;
// }

// int main()
// {
// 	t_setting setting;

// 	parsing(setting.rgb);

	
// 	printf("setting is %d\n", setting.rgb[0]);
// }

// int main()
// {
// 	char *line;
// 	int fd;

// 	fd = open("test.rt", O_RDONLY);
// 	while (1)
// 	{
// 		if (get_next_line(fd, &line) == 1)
// 		{	
// 			printf("line is %s", line);
// 			free(line);
// 		}
// 		else if (get_next_line(fd, &line) == 0)
// 		{
// 			printf("last line is %s", line);
// 			free(line);
// 			break;
// 		}
// 		else
// 			return (-1);
// 	}
// 	return (0);
// }

// double *vector_dir(double a[3], double b[3], double ba[3])
// {
// 	ba[0] = a[0] - b[0];
// 	ba[1] = a[1] - b[1];
// 	ba[2] = a[2] - b[2];
// 	return (ba);
// }

// int main()
// {
// 	// double	*x_temp;
// 	// double	*y_temp;
// 	// double	*ray_temp;

// 	// x_temp = malloc(3 * sizeof(double));
// 	// if (!x_temp)
// 	// 	return NULL;
// 	double a[3] = {1, 2, 3};
// 	double b[3] = {2, 3, 4};
// 	vector_dir(a, b, a);
// 	printf("difference is %f %f %f'\n", a[0], a[1], a[2]);
// }

// typedef struct	s_vars {
// 	void	*mlx;
// 	void	*win;
// 	int	*x;
// 	int	*y;
// }				t_vars;


// int key_hook(t_vars *vars)
// {

// 	mlx_mouse_get_pos(vars->win, vars->x, vars->y);
// 	printf("x y position is %d, %d\n", vars->x[0], vars->y[0]);
// 	return (0);
// }

// int	close(int keycode, t_vars *vars)
// {
// 	if (keycode == )
// 	mlx_destroy_window(vars->mlx, vars->win);
// 	return (0);
// }

// int main()
// {
// 	t_vars	vars;

// 	vars.mlx = mlx_init();
// 	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
// 	// mlx_key_hook(vars.win, key_hook, &vars);
// 	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
// 	mlx_loop(vars.mlx);
// 	return (0);
// }

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	// int	*x;
	// int	*y;
}				t_vars;

// int	key_hook(int keycode, t_vars *vars)
// {
// 	printf("Hello from key_hook!\n");
// 	printf("%d\n", keycode);
// 	// mlx_mouse_get_pos(vars->win, vars->x, vars->y);
// 	// printf("x y position is %d, %d\n", vars->x[0], vars->y[0]);
// 	if (vars)
// 		return (1);
// 	return (0);
// }

int close(int keycode, t_vars *vars)
{
	printf("key is %d\n", keycode);
	mlx_mouse_move(vars->win, 500, 400);
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	// mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 1L<<17, close, &vars);
	mlx_mouse_move(vars.win, 500, 400);
	mlx_loop(vars.mlx);
}



//rewrite check side value and return the right one
double	cal_discriminant(double *co, t_object *object, double *dir, double *o)
{
	double	dn;
	double	a;
	double	b;
	double	c;
	double	con;
	double	discriminant;

	dn = dot_product(dir, object->orientation);
	a = 1 - dn * dn;
	co = vector_dir(o, object->center, co);
	con = dot_product(co, object->orientation);
	b = 2 * dot_product(dir, co) - 2 * con * dn;
	c = dot_product(co, co) - object->diameter[0] * object->diameter[0] - con * con;
	discriminant = b * b - 4 * a * c;
	co[0] = a;
	co[1] = b;
	co[2] = c;
	return (discriminant);
}

double	compare_t_value(t_object *object, double *t, double *dir, double *o)
{
	double *p;
	double dot_p;
	double result;

	p = malloc(3 * sizeof(double));
	//to update the error treatment later #update
	// if (!p)
	// 	Erroro message
	result = INFINITY;
	if (t[0] > 0)
	{
		vector_plus(o, vector_multi2(dir, t[0], p), p);
		vector_dir(p, object->center, p);
		dot_p = dot_product(p, object->center);
		if (dot_p <= object->lenth[0] / 2 && dot_p >= -object->lenth[0] / 2 )
			result = t[0];
	}
	if (t[1] > 0)
	{
		vector_plus(o, vector_multi2(dir, t[1], p), p);
		vector_dir(p, object->center, p);
		dot_p = dot_product(p, object->center);
		if (dot_p <= object->lenth[0] / 2 && dot_p >= -object->lenth[0] / 2 && dot_p < result)
			result = t[1];
	}
	free(p);
	return (result);	
}

double	check_side(t_object *object, double *dir, double o[3], t_result *result)
{
	double	*co;
	double	discriminant;
	double	q;

	co = malloc(3 * sizeof(double));
	if (!co)
		return (0);
	discriminant = cal_discriminant(co, object, dir, o);
	if (discriminant < 0)
	{
		free(co);
		return (0);
	}
	else
	{
		if (co[1] > 0)
			q = - 0.5 * (co[1] + sqrt(discriminant));
		else
			q = - 0.5 * (co[1] - sqrt(discriminant));
		co[0] = q / co[0];//record t1
		co[1] = co[2] / q;//record t2
		q = compare_t_value(object, co, dir, o);
		free(co);
		return (q);
	}
}