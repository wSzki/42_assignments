/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:15:15 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/16 15:15:27 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Z * (n + 1) = (Z * n) ^ 2 + c;
 * Z * n = (Z * (n - 1)) ^ 2 + c;
 * Z = (Z ^ 2) + c;
 *
 * Z = (a +  b * i)^2 + x + y * i;
 * Z = (a ^ 2 + 2abi + (b * i) ^ 2) + (x + y * i);
 * Z = a ^ 2 + i(2ab) + (i ^ 2) * (b ^ 2) + x + y * i;
 * Z = a ^ 2 + i(2ab) + (-1 * (b ^ 2)) + x + y * i;
 * Z = (a ^ 2 - b ^ 2 + x) + i[(2ab + y)]
 *
 *
 * |Z| = sqrt(a ^2 + b ^2);
 * if Z < 2, within mandelbrot
 * il faut savoir que l'ensemble de Mandelbrot est toujours compris entre
 * -2.1 et 0.6 sur l'axe des abscisse et entre
 * -1.2 et 1.2 sur l'axe des ordonnées.
 */

#include "../includes/fractol.h"

static int	fractol_mandelbrot(t_global *g, float x, float y, int n_max)
{
	int		i;
	float	tmp;
	float	a;
	float	b;

	i = 0;
	a = 0;
	b = 0;
	x = g->x_origin + x * g->x_total / WIDTH;
	y = g->y_origin - y * g->y_total / HEIGHT;
	while ((powf(a, 2) + powf(b, 2)) < 4 && i < 1096)
	{
		tmp = a;
		a = powf(a, 2) - powf (b, 2) + x;
		b = (2 * b * tmp) + y;
		i++;
	}
	if (i == n_max)
		return (0x000000);
	return (g->color[i % 32]);
}

static int	fractol_julia(t_global *g, float x, float y, int n_max)
{
	int		i;
	float	tmp;

	i = 0;
	x = g->x_origin + x * g->x_total / WIDTH;
	y = g->y_origin - y * g->y_total / HEIGHT;
	while ((powf(x, 2) + powf(y, 2)) < 4 && i < 1096)
	{
		tmp = x;
		x = powf(x, 2) - powf (y, 2) + g->a;
		y = (2 * y * tmp) + g->b;
		i++;
	}
	if (i == n_max)
		return (0x000000);
	return (g->color[i % 32]);
}

void	fractol_run(t_global *g)
{
	float	x;
	float	y;
	int		color;

	color = 0x000000;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (g->fractal_type == 'm')
				color = fractol_mandelbrot(g, x, y, 1096);
			if (g->fractal_type == 'j')
				color = fractol_julia(g, x, y, 1096);
			my_mlx_pixel_put(g, (int)x, (int)y, color);
		}
	}
}
