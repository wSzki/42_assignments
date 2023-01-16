/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:15:54 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/16 15:15:55 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	fractol_zoom(t_global *g, char direction)
{
	float	x_offset;
	float	y_offset;

	x_offset = 0.0;
	y_offset = 0.0;
	if (direction == '+')
	{
		g->x_total *= 0.9;
		g->y_total *= 0.9;
	}
	if (direction == '-')
	{
		g->x_total *= 1.1;
		g->y_total *= 1.1;
	}
	if (g->fractal_type == 'm')
		x_offset = -0.55;
	g->x_origin = x_offset - (g->x_total * 0.5);
	g->y_origin = y_offset + (g->y_total * 0.5);
	fractol_run(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

int	fractol_get_key_event(int key, t_global *g)
{
	if (key == PLUS)
		fractol_zoom(g, '+');
	if (key == MINUS)
		fractol_zoom(g, '-');
	if (key == ECHAP)
		free_all_and_exit(g);
	return (1);
}

int	fractol_get_scroll_event(int key, int x, int y, t_global *g)
{
	(void)x;
	(void)y;
	if (key == WHEEL_UP)
		fractol_zoom(g, '+');
	if (key == WHEEL_DOWN)
		fractol_zoom(g, '-');
	return (1);
}

void	fractol_set_hooks(t_global *g)
{
	mlx_key_hook(g->win, fractol_get_key_event, g);
	mlx_mouse_hook(g->win, fractol_get_scroll_event, g);
}
