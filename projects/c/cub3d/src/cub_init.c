/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:37:49 by wszurkow          #+#    #+#             */
/*   Updated: 2022/03/24 15:22:01 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_init_struct(t_global **global)
{
	t_global	*g;

	g = *global;
	g->d.n = NULL;
	g->d.s = NULL;
	g->d.w = NULL;
	g->d.e = NULL;
	g->d.r = NULL;
	g->p.x = 0;
	g->p.y = 0;
	g->p.angle = 0;
	g->d.c = -1;
	g->d.f = -1;
	g->m.map = NULL;
	g->m.rows = 0;
	g->m.cols = 0;
	g->m.player = 0;
	g->m.in_map = 0;
	g->w.w = WIDTH;
	g->w.h = HEIGHT;
	g->mm.floor_color = MM_FLOOR_COLOR;
	g->mm.wall_color = MM_WALL_COLOR;
	g->mm.player_color = MM_PLAYER_COLOR;
	g->split = NULL;
	g->line = NULL;
}

static void	cub_init_mlx_pointers(t_global **global)
{
	t_global	*g;

	g = *global;
	g->fd = -1;
	g->x.mlx = NULL;
	g->x.win = NULL;
	g->x.buffer.img = NULL;
	g->x.background.img = NULL;
	g->x.north.img = NULL;
	g->x.east.img = NULL;
	g->x.south.img = NULL;
	g->x.west.img = NULL;
	g->x.minimap.img = NULL;
	g->x.mm_floor.img = NULL;
	g->x.mm_player.img = NULL;
	g->x.mm_wall.img = NULL;
}

void	cub_init(t_global **g)
{
	cub_init_struct(g);
	cub_init_mlx_pointers(g);
}
