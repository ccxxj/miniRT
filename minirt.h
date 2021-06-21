/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Xiaojing <Xiaojing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/21 21:11:55 by Xiaojing      #+#    #+#                 */
/*   Updated: 2021/05/30 17:29:00 by Xiaojing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <mlx.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_setting {
	double		size[2];
	double		lighting_r[1];
	double		rgb[3];
	double		pix[2];
}				t_setting;

typedef struct s_camera {
	double			coordinates[3];
	double			orientation[3];
	double			right[3];
	double			up[3];
	double			bottom_left[3];
	double			x_unit[3];
	double			y_unit[3];
	double			fov[1];
	struct s_camera	*next;
}					t_camera;

typedef struct s_light {
	double			coordinates[3];
	double			brightness[1];
	double			rgb[3];
	struct s_light	*next;
}					t_light;

typedef struct s_object {
	char			type[2];
	double			center[3];
	double			diameter[1];
	double			lenth[1];
	double			rgb[3];
	double			coordinates_1[3];
	double			coordinates_2[3];
	double			coordinates_3[3];
	double			orientation[3];
	double			tri_vect1[3];
	double			tri_vect2[3];
	double			normal[3];
	double			p[3];
	struct s_object	*next;
}					t_object;

typedef struct s_result
{
	double		t_min;
	double		shade;
	double		rgb[3];
	double		p[3];
	double		normal[3];
	double		ambient[3];
	double		diffuse[3];
	double		intensity[3];
}				t_result;

typedef struct s_triangle
{
	double		pvec[3];
	double		qvec[3];
	double		ov0[3];
}				t_triangle;

typedef struct s_parameters
{
	int			i;
	int			j;
	double		nb;
	int			neg;
}				t_parameters;

typedef struct s_vars {
	void			*mlx;
	void			*win;
	int				sizex[1];
	int				sizey[1];
	int				flag[2];
	int				cameranb;
	int				listsize;
	int				save;
	unsigned char	**buffer;
	t_image			img;
	t_object		*object;
	t_camera		*camera;
	t_light			*light;
	t_setting		setting;
}					t_vars;

/*parsingredo*/
void	parse(int fd, t_vars *vars);
void	initialize_objects1(char *line, t_object **object);
void	initialize_objects2(char *line, t_object **object);
void	initialize_objects3(char *line, t_object **object);
void	initialize_objects4(char *line, t_object **object);

//minirt*/
void	minirt(int fd, int save);

//get next line*/
int		get_next_line(int fd, char **line);

/*verctor utils*/
double	*vector_dir(double a[3], double b[3], double ba[3]);
double	*normalization(double *a);
double	dot_product(double a[3], double b[3]);
double	*vector_plus(double a[3], double b[3], double ab[3]);
double	*vector_multi(double a[3], double b);
double	*cross_product(double a[3], double b[3], double c[3]);
double	*matrix_mult(double a[4][4], double b[4], double c[4]);
double	*vector_multi2(double a[3], double b, double c[3]);

/*loop.c*/
int		cal_return(t_object *objects, t_camera *camera, t_light *light,
			t_setting *setting);
void	loop_obj(t_object *head, double o[3], double *pri_ray,
			t_result *result);

//camera matrix*/
void	exp_handle(double right[3], double up[3], double o);
void	camera_set(t_camera *camera, t_setting *setting);
double	*cast_ray(t_camera *camera, int x, int y, double *pri_ray);

/*cylinder*/
void	cy_normal(double *p, t_object *object);
double	cal_top_intersect(t_object *object, double dir[3], double o[3]);
double	cal_bottom_intersect(t_object *object, double dir[3], double o[3]);
double	check_side(t_object *object, double *dir, double o[3]);

/*intersect*/
double	cal_sp_intersect(double o[3], double c[3], double dir[3], double r);
double	cal_pl_intersect(double p0[3], double n[3], double dir[3], double o[3]);
double	cal_tr_intersect(t_object *object, double dir[3], double o[3]);
void	update_normal(double p[3], double o[3], double orientation[3],
			double normal[3]);
void	cal_shade(t_result *result, double light_ray[3]);

/*light*/
void	transfer_rgb(double *rgb, double *intensity, double ratio);
void	final_intensity(t_result *result);
int		cal_color(double intensity[3], int t, double rgb[3]);
int		check_light_intersect(t_light *light, t_result *result,
			t_object *object, t_setting *setting);

/*render*/
int		create_trgb(int t, int r, int g, int b);
void	render(int cameranb, t_vars *vars);

/*square*/
void	process_square(t_object *object);
int		check_sq_intersect(double t, t_object *object, double dir[3],
			double o[3]);

/*utils*/
int		ft_lstsize(t_camera *lst);
void	create_vector(double **vector);
void	create_object(t_object	**object);

/*utils2*/
void	initialize_parameters(t_parameters *d);
void	initialize_flag(t_vars *vars);
void	free_array(char **array, int nb);

/*buffer minirt*/
void	decode_color(int trgb, unsigned char buffer[3]);
void	create_buffer(t_vars *vars);
void	free_buffer(t_vars *vars);

/*bmp*/
void	write_bmp(t_vars *vars);

/*loop2*/
double	get_t(t_object *object);
double	cal_return2(t_result *result, t_light *light, t_setting *setting,
			t_object *objects);

/*free */
void	free_list(t_vars *vars);

/*check input */
void	check_general_input(char *line);
void	check_range(double *vec, int low, int high, int nb);
void	check_normalization(double *vec);
void	check_float(char *str);
void	parse_elements(double *dest, char *str, int nb, int bool);
double	convert_nbr(char *str);

/*parsing redo */

/*split */
char	**ft_split(char const *s, char c, int n);

/*error */
void	print_error(int a);

/*utils3*/
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);

#endif