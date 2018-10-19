/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mlx2.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/09 12:04:36 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/09 12:36:43 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		reset_mlx(t_mlx *mlx)
{
	mlx->startx = 0;
	mlx->endx = WINW / 4;
	mlx->starty = 0;
	mlx->endy = WINH / 2;
}

static void		threading(t_mlx *mlx, void *(func)(void*))
{
	pthread_t	th[8];
	int			i;

	i = 0;
	if (!mlx->img_ptr)
		new_image(mlx);
	while (mlx->endy <= WINH)
	{
		mlx->startx = 0;
		mlx->endx = WINW / 4;
		while (mlx->endx <= WINW)
		{
			pthread_create(&th[i], NULL, func, mlx_cpy(mlx));
			mlx->startx += WINW / 4;
			mlx->endx += WINW / 4;
			i++;
		}
		mlx->starty += WINH / 2;
		mlx->endy += WINH / 2;
	}
	i = -1;
	reset_mlx(mlx);
	while (++i < 8)
		pthread_join(th[i], NULL);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img_ptr, 0, 0);
}

void			start_mthread(t_mlx *mlx)
{
	mlx_clear_window(mlx->ptr, mlx->win);
	if (mlx->fractal == JULIA)
		threading(mlx, &julia);
	if (mlx->fractal == MANDEL || mlx->fractal == BURNING_SHIP)
		threading(mlx, &mandelbrot);
	display_fractol(mlx);
}

void			set_fractal_mlx(t_mlx *mlx, char *str)
{
	if (ft_strcmp(str, "mandelbrot") == 0)
		mlx->fractal = MANDEL;
	if (ft_strcmp(str, "julia") == 0)
		mlx->fractal = JULIA;
	if (ft_strcmp(str, "burningship") == 0)
		mlx->fractal = BURNING_SHIP;
}

void			display_fractol(t_mlx *mlx)
{
	char *it;

	it = ft_itoa(mlx->iteration);
	if (mlx->fractal == JULIA)
		mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x1FFFFF,
					"Fractal : Julia");
	if (mlx->fractal == MANDEL)
		mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x1FFFFF,
					"Fractal : Mandelbrot");
	if (mlx->fractal == BURNING_SHIP)
		mlx_string_put(mlx->ptr, mlx->win, 0, 0, 0x1FFFFF,
					"Fractal : Burning Ship");
	mlx_string_put(mlx->ptr, mlx->win, 0, 15, 0x1FFFFF, "Iteration : ");
	mlx_string_put(mlx->ptr, mlx->win, 115, 15, 0x1FFFFF, it);
	ft_strdel(&it);
}
