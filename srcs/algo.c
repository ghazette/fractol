/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   thread.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/05 14:50:01 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/09 12:19:32 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		calc_mandel(t_mandelbrot *mandel, t_mlx *mlx, size_t *p)
{
	mandel->rc = (mandel->minx + (mandel->maxx - mandel->minx) /
			(WINW * mlx->zoom) * mlx->startx) + mlx->movex;
	mandel->ic = (mandel->miny + (mandel->maxy - mandel->miny) /
			(WINH * mlx->zoom) * mlx->starty) + mlx->movey;
	mandel->rz = 0;
	mandel->iz = 0;
	mandel->k = 0;
	while (mandel->k < mlx->iteration && mandel->rz * mandel->rz +
			mandel->iz * mandel->iz < 4)
	{
		mandel->r = (mlx->fractal == BURNING_SHIP) ? fabs(mandel->rz) :
					mandel->rz;
		mandel->i = (mlx->fractal == BURNING_SHIP) ? fabs(mandel->iz) :
					mandel->iz;
		mandel->rz = mandel->r * mandel->r - mandel->i * mandel->i + mandel->rc;
		mandel->iz = 2 * mandel->r * mandel->i + mandel->ic;
		mandel->k++;
	}
	mlx->img_data[*p] = (char)(mandel->k * 8);
	mlx->img_data[*p + 1] = (char)(mandel->k * 5);
	mlx->img_data[*p + 2] = (char)(mandel->k * 0);
	mlx->img_data[*p + 3] = (char)0;
	*p += 4;
	mlx->startx++;
}

void			*mandelbrot(void *mlxp)
{
	t_mandelbrot	*mandel;
	t_mlx			*mlx;
	size_t			xsave;
	size_t			p;

	mlx = (t_mlx*)mlxp;
	xsave = mlx->startx;
	if (!(mandel = mandelbrot_init()))
		pthread_exit(NULL);
	p = (mlx->starty * mlx->sl) + (mlx->startx * 4);
	while (mlx->starty < mlx->endy)
	{
		mlx->startx = xsave;
		while (mlx->startx < mlx->endx)
			calc_mandel(mandel, mlx, &p);
		p += mlx->sl - ((WINW / 4) * 4);
		mlx->starty++;
	}
	free(mlx);
	free(mandel);
	pthread_exit(NULL);
}

static void		calc_julia(t_mlx *mlx, t_julia *julia, size_t *p)
{
	julia->newre = 1.5 * (mlx->startx - WINW / 2) / (0.5 * mlx->zoom * WINW) +
		mlx->movex;
	julia->newim = (mlx->starty - WINH / 2) / (0.5 * mlx->zoom * WINH) +
		mlx->movey;
	julia->k = 0;
	while (julia->k < mlx->iteration && (julia->newre * julia->newre +
				julia->newim * julia->newim) < 4)
	{
		julia->oldre = julia->newre;
		julia->oldim = julia->newim;
		julia->newre = julia->oldre * julia->oldre - julia->oldim *
			julia->oldim + julia->cre;
		julia->newim = 2 * julia->oldre * julia->oldim + julia->cim;
		julia->k++;
	}
	mlx->img_data[*p] = (char)(julia->k * 44);
	mlx->img_data[*p + 1] = (char)(julia->k * 48949);
	mlx->img_data[*p + 2] = (char)(julia->k * 51791759);
	mlx->img_data[*p + 3] = (char)0;
	*p += 4;
	mlx->startx++;
}

void			*julia(void *mlxp)
{
	t_mlx	*mlx;
	t_julia	*julia;
	size_t	p;
	int		xsave;

	mlx = (t_mlx*)mlxp;
	p = (mlx->starty * mlx->sl) + (mlx->startx * 4);
	xsave = mlx->startx;
	if (!(julia = julia_init(mlx)))
		pthread_exit(NULL);
	while (mlx->starty < mlx->endy)
	{
		mlx->startx = xsave;
		while (mlx->startx < mlx->endx)
			calc_julia(mlx, julia, &p);
		p += mlx->sl - ((WINW / 4) * 4);
		mlx->starty++;
	}
	free(julia);
	free(mlx);
	pthread_exit(NULL);
}
