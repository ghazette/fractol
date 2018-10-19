/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dealkey.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ghazette <ghazette@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/02 11:11:27 by ghazette     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/02 11:11:27 by ghazette    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		dealkey2(int key, t_mlx *mlx)
{
	if (key >= 123 && key <= 126)
	{
		mlx->movex -= (key == 123) ? 0.3 / mlx->zoom : 0;
		mlx->movex += (key == 124) ? 0.3 / mlx->zoom : 0;
		mlx->movey -= (key == 126) ? 0.3 / mlx->zoom : 0;
		mlx->movey += (key == 125) ? 0.3 / mlx->zoom : 0;
		start_mthread(mlx);
	}
	if (key == MINUS && mlx->iteration > 20)
	{
		mlx->iteration -= 10;
		start_mthread(mlx);
	}
	if (key == PLUS)
	{
		mlx->iteration += 10;
		start_mthread(mlx);
	}
}

int				dealkey(int key, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (key == SPACE && mlx->fractal == JULIA)
		mlx->lockmouse = (mlx->lockmouse) ? 0 : 1;
	if (key == ESCAPE)
	{
		mlx_destroy_image(mlx->ptr, mlx->img_ptr);
		free(mlx);
		exit(0);
	}
	if (mlx->lockmouse)
		return (1);
	dealkey2(key, mlx);
	return (1);
}

int				dealmouse(int key, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	x++;
	y++;
	if (mlx->lockmouse)
		return (1);
	if (key == SCROLLUP)
	{
		mlx->zoom *= 1.1;
		start_mthread(mlx);
	}
	if (key == SCROLLDOWN && mlx->zoom > 0.1)
	{
		mlx->zoom /= 1.1;
		start_mthread(mlx);
	}
	return (1);
}

int				motion(int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx*)param;
	if (mlx->lockmouse)
	{
		mlx->cre = (2 * ((WINW / 2) - (double)x)) / (WINW / 2);
		mlx->cim = (-2 * ((WINH / 2) - (double)y)) / (WINH / 2);
		if (mlx->cre > 2)
			mlx->cre = 2;
		if (mlx->cre < -2)
			mlx->cre = -2;
		if (mlx->cim > 2)
			mlx->cim = 2;
		if (mlx->cim < -2)
			mlx->cim = -2;
		start_mthread(mlx);
	}
	return (1);
}
