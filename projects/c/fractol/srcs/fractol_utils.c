/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:15:47 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/16 17:13:33 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_global *g, int x, int y, int color)
{
	char	*dst;

	dst = g->addr + (y * g->line_length + x * (g->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	fractol_print_and_exit(char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
}

int	fractol_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	fractol_input_check(int ac, char **av)
{
	if (ac == 1)
		fractol_print_and_exit("No input parameter given");
	if (fractol_strcmp(av[1], "mandelbrot") == 0)
	{
		if (ac != 2)
			fractol_print_and_exit(\
					"'mandelbrot' does not take additional parameters");
	}
	else if (fractol_strcmp(av[1], "julia") == 0)
	{
		if (ac != 2 && ac != 3)
			fractol_print_and_exit(\
					"'julia' takes 0 or 1 parameter (1, 2, 3 or 4)");
	}
	else
		fractol_print_and_exit("Invalid fractal name");
}
