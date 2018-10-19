/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/02 10:43:11 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/09 12:33:59 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_mlx			*mlx_init_all(int width, int height, char *name)
{
	t_mlx *mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, width, height, name);
	mlx->img_data = NULL;
	mlx->img_ptr = NULL;
	mlx->bpp = 0;
	mlx->sl = 0;
	mlx->zoom = 0.5;
	mlx->movex = 0;
	mlx->movey = 0;
	mlx->iteration = 50;
	mlx->startx = 0;
	mlx->endx = WINW / 4;
	mlx->starty = 0;
	mlx->endy = WINH / 2;
	mlx->cre = -0.7;
	mlx->cim = 0.27;
	mlx->lockmouse = 0;
	mlx->fractal = 0;
	return (mlx);
}

t_mandelbrot	*mandelbrot_init(void)
{
	t_mandelbrot *mandel;

	if (!(mandel = (t_mandelbrot *)malloc(sizeof(t_mandelbrot))))
		return (NULL);
	mandel->minx = -2.4;
	mandel->maxx = 2.4;
	mandel->miny = -1.8;
	mandel->maxy = 1.8;
	mandel->x = 0;
	mandel->y = 0;
	mandel->i = 0;
	mandel->rc = 0;
	mandel->ic = 0;
	mandel->r = 0;
	return (mandel);
}

t_julia			*julia_init(t_mlx *mlx)
{
	t_julia *julia;

	if (!(julia = (t_julia *)malloc(sizeof(t_julia))))
		return (NULL);
	julia->cre = mlx->cre;
	julia->cim = mlx->cim;
	julia->newre = 0;
	julia->newim = 0;
	julia->oldre = 0;
	julia->oldim = 0;
	julia->k = 0;
	return (julia);
}

void			new_image(t_mlx *mlx)
{
	int		endian;

	mlx->img_ptr = mlx_new_image(mlx->ptr, WINW, WINH);
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->sl,
									&endian);
}

t_mlx			*mlx_cpy(t_mlx *src)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->ptr = src->ptr;
	mlx->win = src->win;
	mlx->sl = src->sl;
	mlx->bpp = src->bpp;
	mlx->img_ptr = src->img_ptr;
	mlx->img_data = src->img_data;
	mlx->zoom = src->zoom;
	mlx->movex = src->movex;
	mlx->movey = src->movey;
	mlx->iteration = src->iteration;
	mlx->startx = src->startx;
	mlx->endx = src->endx;
	mlx->starty = src->starty;
	mlx->endy = src->endy;
	mlx->cre = src->cre;
	mlx->cim = src->cim;
	mlx->fractal = src->fractal;
	return (mlx);
}
