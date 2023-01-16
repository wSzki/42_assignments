/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:20:43 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/16 17:39:51 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define HEIGHT 250.0
# define WIDTH 250.0
# define X_BORDER -2.05
# define Y_BORDER 1.55
# define RELATIVE_SIZE 3.0

# define WHEEL_UP 5
# define WHEEL_DOWN 4

# define ECHAP 65307
# define SPACE 32
# define PLUS 61
# define MINUS 45

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "../ext/minilibx-linux/mlx.h"

typedef struct s_global
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*color;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	fractal_type;
	float	x_origin;
	float	y_origin;
	float	x_total;
	float	y_total;
	float	a;
	float	b;
}				t_global;

int		fractol_strcmp(char *s1, char *s2);
void	fractol_input_check(int ac, char **av);
void	fractol_run(t_global *g);
void	free_all_and_exit(t_global *g);
void	fractol_set_hooks(t_global *g);
void	my_mlx_pixel_put(t_global *g, int x, int y, int color);
void	fractol_set_color(t_global *g);
void	fractol_set_additional_colors(t_global *g);
void	fractol_data_init(t_global *g, int ac, char **av);

#endif
