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

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

// int		add_shade(double a, int trgb)
// {
// 	int	t;
// 	int	r;
// 	int	g;
// 	int	b;

// 	t = a * (get_t(trgb));
// 	r = a * (get_r(trgb));
// 	// printf("color r is %d\n", r);
// 	g = a * (get_g(trgb));
// 	b = a * (get_b(trgb));
// 	return (create_trgb(t, r, g, b));
// }

int		add_shade(double a, int t, int r, int g, int b)
{
	t = a * t;
	r = a * r;
	g = a * g;
	b = a * b;
	return (create_trgb(t, r, g, b));
}

int	main(void)
{
    void    *mlx;
    void    *mlx_win;
	t_data	img;
	int		a;
	int		b;
	// t_setting	setting;

	a = 0;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1000, 800, "my first window");
    img.img = mlx_new_image(mlx, 1000, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (a < 1000)
	{
		b = 0;
		while (b < 800)
		{
		// circle
			if (((a - 500) * (a - 500) + (b - 300) * (b - 300)) < 900)
				// my_mlx_pixel_put(&img, a, b, add_shade(1, create_trgb(0, 255, 255, 255)));
				my_mlx_pixel_put(&img, a, b, create_trgb(0, 0, 255, 255));
			else if (((a - 500) * (a - 500) + (b - 300) * (b - 300)) < 1500)
				// my_mlx_pixel_put(&img, a, b, add_shade(0.8, create_trgb(0, 0, 255, 255)));
				my_mlx_pixel_put(&img, a, b, add_shade(0.8, 0, 0, 255, 255));
			else if (((a - 500) * (a - 500) + (b - 300) * (b - 300)) < 2500)
				// my_mlx_pixel_put(&img, a, b, add_shade(0.6, create_trgb(0, 0, 255, 255)));
				my_mlx_pixel_put(&img, a, b, add_shade(0.6, 0, 0, 255, 255));
			else if (((a - 500) * (a - 500) + (b - 300) * (b - 300)) < 3500)
				// my_mlx_pixel_put(&img, a, b, add_shade(0.4, create_trgb(0, 0, 255, 255)));
				my_mlx_pixel_put(&img, a, b, add_shade(0.4, 0, 0, 255, 255));
			else if (((a - 500) * (a - 500) + (b - 300) * (b - 300)) < 4500)
				// my_mlx_pixel_put(&img, a, b, add_shade(0.2, create_trgb(0, 0, 255, 255)));
				my_mlx_pixel_put(&img, a, b, add_shade(0.2, 0, 0, 255, 255));
			b++;
		}
		a++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
