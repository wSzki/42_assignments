/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_data_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:24:06 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/16 17:41:43 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	fractol_set_const(t_global *g, float a, float b)
{
	g->a = a;
	g->b = b;
}

static void	fractol_set_julia(t_global *g, char **av)
{
	if (av[2][0] == '1' && av[2][1] == 0)
		fractol_set_const(g, -0.70716, -0.3842);
	else if (av[2][0] == '2' && av[2][1] == 0)
		fractol_set_const(g, 0.285, 0);
	else if (av[2][0] == '3' && av[2][1] == 0)
		fractol_set_const(g, 0.285, 0.01);
	else if (av[2][0] == '4' && av[2][1] == 0)
		fractol_set_const(g, -0.8, 0.156);
	else
	{
		printf("Error\n");
		printf("Invalid 'julia' parameters\n");
		printf("Must be 1, 2, 3 or 4\n");
		exit(1);
	}
}

void	fractol_data_init(t_global *g, int ac, char **av)
{
	if (g->fractal_type == 'm')
	{
		g->x_origin = -2.05;
		g->y_origin = 1.5;
		g->x_total = 3.0;
		g->y_total = 3.0;
	}
	if (g->fractal_type == 'j')
	{
		g->x_origin = -1.5;
		g->y_origin = 1.5;
		g->x_total = 3.0;
		g->y_total = 3.0;
		if (ac == 3)
			fractol_set_julia(g, av);
		else
			fractol_set_const(g, -0.4, 0.6);
	}
}
