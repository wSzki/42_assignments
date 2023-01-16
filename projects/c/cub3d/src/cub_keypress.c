/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keypress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:33:58 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/02 18:36:01 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	up_down(t_global *g, int b_f, t_vector v, int offset)
{
	int				y;
	int				x;
	t_coord			next_step;
	t_coord			current_step;
	unsigned int	dir;

	offset = 0;
	current_step.x = g->p.x;
	current_step.y = g->p.y;
	v.start = current_step;
	v.end = current_step;
	next_step = cub_vector_end(current_step, PIXELS_PER_STEP, g->p.angle + b_f);
	cub_get_wall_pos(g, v, g->p.angle + b_f, &dir);
	if (dir == NO || dir == ES)
		offset = -1;
	y = ((next_step.y + offset) / (double)g->mm.block_size);
	x = ((next_step.x + offset) / (double)g->mm.block_size);
	if (g->m.map[y] && g->m.map[y][x])
	{	
		if (g->m.map[y][x] != '1')
		{
			g->p.x = next_step.x;
			g->p.y = next_step.y;
		}
	}
}

int	cub_keypress(int keycode, t_global *g)
{
	t_vector		v;

	if (g->p.angle > CIRCLE)
		g->p.angle -= CIRCLE;
	if (g->p.angle < 0)
		g->p.angle += CIRCLE;
	if (keycode == W_KEY)
		up_down(g, 0, v, 0);
	if (keycode == S_KEY)
		up_down(g, 180, v, 0);
	if (keycode == A_KEY)
		up_down(g, 270, v, 0);
	if (keycode == D_KEY)
		up_down(g, 90, v, 0);
	if (keycode == LEFT)
		g->p.angle -= DEGREES_PER_STEP;
	if (keycode == RIGHT)
		g->p.angle += DEGREES_PER_STEP;
	if (keycode == ESC)
	{
		cub_free_all(g);
		exit(0);
	}
	cub_display_refresh(g);
	return (0);
}
