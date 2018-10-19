/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/02 11:45:49 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/02 13:55:25 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		main(int ac, char **av)
{
	t_mlx *mlx;

	if (ac > 1)
	{
		if (!(mlx = mlx_init_all(WINW, WINH, APP_NAME)))
			exit(1);
		set_fractal_mlx(mlx, av[1]);
		if (mlx->fractal)
		{
			start_mthread(mlx);
			mlx_hook(mlx->win, 2, 1L, &dealkey, mlx);
			mlx_hook(mlx->win, 6, 0, &motion, mlx);
			mlx_mouse_hook(mlx->win, &dealmouse, mlx);
			mlx_loop(mlx->ptr);
		}
		else
			ft_printf("Usage : ./fractol mandelbrot | julia | burningship\n");
	}
	else
		ft_printf("Usage : ./fractol mandelbrot | julia | burningship\n");
	return (0);
}
