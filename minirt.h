/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 11:46:42 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/15 22:08:28 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <stdio.h>//to remove later
#include <stdlib.h>
#include <fcntl.h>
# include <stddef.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


typedef struct  s_setting {
	// double	width;
	// double	height;
	double	size[2];
	double	lighting_r[1];
	// int		r;
	// int		g;
	// int		b;
	double		rgb[3];
}               t_setting;

typedef struct  s_camera {
	double	coordinates[3];
	double	orientation[3];
	double	right[3];
	double	up[3];
	double	bottom_left[3];
	double	x_unit[3];
	double	y_unit[3];
	double	fov[1];
	struct s_camera	*next;
}				t_camera;

typedef struct  s_light {
	double	coordinates[3];
	// double	brightness;
	double	brightness[1];
	double		rgb[3];
	// double	r;
	// double	g;
	// double	b;
	struct	s_light	*next;
}				t_light;

typedef struct  s_object {
	char	type[2];
	double	center[3];
	double	diameter[1];
	double	lenth[1];
	double		rgb[3];
	double	coordinates_1[3];
	double	coordinates_2[3];//sq up vector
	double	coordinates_3[3];//sq right vector
	double	orientation[3];
	double	tri_vect1[3];
	double	tri_vect2[3];
	double	normal[3];
	double	p[3];
	struct	s_object *next;
}				t_object;

typedef struct		s_list
{
	char	*rest_line;
	char	buf[BUFFER_SIZE + 1];
	int		index_n;
	int		flag;
	int		i;
	int		result;
	int		initialization;
}					t_store;

typedef struct		s_result
{
	double	t_min;
	double	shade;
	double	rgb[3];
	double	p[3];
	double	normal[3];
}					t_result;


double	cal_abc(double o[3], double c[3], double dir[3], float r, double light[3]);
// double	check_return(double o[3], double c[3], double FOV, int x, int y, float r, t_setting *setting);
void	exp_handle(double right[3], double up[3], double o);
double *vector_dir(double a[3], double b[3], double ba[3]);
double	*normalization(double *a);
double	dot_product(double a[3], double b[3]);
double *vector_plus(double a[3], double b[3], double ab[3]);
double	*vector_multi(double a[3], double b);
double	*cross_product(double a[3], double b[3], double c[3]);
double	*matrix_mult(double a[4][4], double b[4], double c[4]);
double	*vector_multi2(double a[3], double b, double c[3]);
// double cal_shade(double t, double o[3], t_object *object, double *dir, t_light *light);
void	cal_shade(t_result *result, double light_ray[3]);
int		add_shade(double a, int t, int r, int g, int b);
// int		cal_return(t_object *objects, t_setting *setting, t_camera *camera, t_light *light, int x, int y);
int		cal_return(t_object *objects, t_camera *camera, t_light *light, int x, int y);
int		create_trgb(int t, int r, int g, int b);
double cal_sp_intersect(double o[3], double c[3], double dir[3], double r);
double	cal_pl_intersect(double p0[3], double n[3], double dir[3], double o[3]);
double	cal_tr_intersect(t_object *object, double dir[3], double o[3]);
double	check_side(t_object *object, double *dir, double o[3]);
// double	check_side(t_object *object, double *dir, double o[3], t_result *result);
void cy_normal(double *p, t_object *object);
double	cal_top_intersect(t_object *object, double dir[3], double o[3]);
double	cal_bottom_intersect(t_object *object, double dir[3], double o[3]);
//get next line functions
void				ft_bzero(void *str, size_t n);
int					ft_strlen(const char *s);
int					get_next_line(int fd, char **line);
int					check_n(char *str);
char				*ft_realloc(char *ptr, int size);
//parsing
void	parsing(char *line, t_setting *setting, t_camera **camera, t_light **light, t_object **object);

void camera_set(t_camera *camera, t_setting *setting);


void	update_normal(double p[3], double o[3], double orientation[3], double normal[3]);
double	*cast_ray(t_camera *camera, int x, int y, double *pri_ray);

//square
void	process_square(t_object *object);
int		check_sq_intersect(double t, t_object *object, double dir[3], double o[3]);

#endif
