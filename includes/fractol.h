/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/02 10:44:02 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/09 12:40:09 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# include <math.h>
# include <pthread.h>
# define APP_NAME "Fractol"
# define WINH 1000
# define WINW 1000
# define JULIA 0x100
# define MANDEL 0x101
# define BURNING_SHIP 0x102
# define ESCAPE 53
# define PLUS 69
# define MINUS 78
# define SPACE 49
# define SCROLLUP 4
# define SCROLLDOWN 5

typedef struct		s_mandelbrot
{
	double			minx;
	double			maxx;
	double			miny;
	double			maxy;
	double			rc;
	double			ic;
	double			rz;
	double			iz;
	double			r;
	double			i;
	int				k;
	long long int	x;
	long long int	y;
}					t_mandelbrot;

typedef struct		s_julia
{
	double			cre;
	double			cim;
	double			newre;
	double			newim;
	double			oldre;
	double			oldim;
	int				k;
}					t_julia;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img_ptr;
	char			*img_data;
	int				bpp;
	int				sl;
	double			zoom;
	double			movex;
	double			movey;
	int				iteration;
	int				startx;
	int				endx;
	int				starty;
	int				endy;
	double			cre;
	double			cim;
	int				lockmouse;
	int				fractal;
}					t_mlx;

/*
** MLX FUNC
*/

t_mlx				*mlx_init_all(int width, int height, char *name);
void				set_fractal_mlx(t_mlx *mlx, char *str);
t_mlx				*mlx_cpy(t_mlx *src);
void				new_image(t_mlx *mlx);

/*
** KEY DETECTION
*/

int					dealkey(int key, void *param);
int					dealmouse(int key, int x, int y, void *param);
int					motion(int x, int y, void *param);

/*
** FRACTAL FUNC RELATED
*/

t_mandelbrot		*mandelbrot_init(void);
t_julia				*julia_init(t_mlx *mlx);
void				*mandelbrot(void *mlxp);
void				*julia(void *mlxp);
void				start_mthread(t_mlx *mlx);
void				display_fractol(t_mlx *mlx);

#endif
