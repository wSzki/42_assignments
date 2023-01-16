/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:14:44 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/18 14:57:25 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractol.h"

static void	fractol_catch_null(t_global *g, void *ptr)
{
	if (!ptr)
	{
		printf("Error\nmalloc failed at address %p", ptr);
		free_all_and_exit(g);
	}
}

static t_global	*fractol_init(char *str)
{
	t_global	*g;

	g = malloc(sizeof(t_global));
	if (!g)
	{
		printf("Error\n %s", "*g malloc failed");
		exit(1);
	}
	g->mlx = NULL;
	g->win = NULL;
	g->img = NULL;
	g->addr = NULL;
	g->color = NULL;
	fractol_set_color(g);
	g->fractal_type = str[0];
	g->mlx = mlx_init();
	fractol_catch_null(g, g->mlx);
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "Fract-ol");
	fractol_catch_null(g, g->win);
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	fractol_catch_null(g, g->img);
	g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel,
			&g->line_length, &g->endian);
	fractol_catch_null(g, g->addr);
	return (g);
}

void	free_all_and_exit(t_global *g)
{
	if (g->mlx && g->img)
	{
		mlx_destroy_image(g->mlx, g->img);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free(g->color);
	free(g);
	exit(0);
}

int	main(int ac, char **av)
{
	t_global	*g;

	fractol_input_check(ac, av);
	g = fractol_init(av[1]);
	fractol_data_init(g, ac, av);
	fractol_run(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	fractol_set_hooks(g);
	mlx_loop(g->mlx);
	free_all_and_exit(g);
}
