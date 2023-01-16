/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 01:54:52 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/02 18:47:32 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	end_cub(t_global *g)
{
	cub_free_all(g);
	exit(0);
}

void	cub_display(t_global *g)
{
	cub_display_refresh(g);
	mlx_hook(g->x.win, 33, 1L << 17, &end_cub, g);
	mlx_hook(g->x.win, KeyPress, KeyPressMask, cub_keypress, g);
	if (mlx_loop(g->x.mlx) != 1)
		cub_error_str(g, MERR_MLX);
}
