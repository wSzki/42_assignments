/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_wall_pos_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 03:53:31 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/28 16:33:57 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	get_first_out_h(t_global *g, t_vector v, double ra)
{
	if (ra == WEST || ra == EAST)
	{
		v.end.x = g->p.x;
		v.end.y = g->p.y;
	}
	else if (ra > WEST && ra < EAST)
	{
		v.end.y = (int)(g->p.y / g->mm.block_size) * g->mm.block_size - 0.0001;
		v.end.x = g->p.x + (fabs(g->p.y - v.end.y) * (1 / tan(ra)));
	}
	else
	{
		v.end.y = g->p.y + (g->mm.block_size -(g->p.y % g->mm.block_size));
		v.end.x = ((g->p.y - v.end.y) * (1 / tan(ra))) + g->p.x;
	}
	return (v);
}

t_vector	get_first_out_v(t_global *g, t_vector v, double ra)
{
	if (ra == NORTH || ra == SOUTH)
	{
		v.end.x = g->p.x;
		v.end.y = g->p.y;
	}
	else if (ra > NORTH && ra < SOUTH)
	{
		v.end.x = (int)(g->p.x / g->mm.block_size) * g->mm.block_size - 0.0001;
		v.end.y = g->p.y + (fabs(g->p.x - v.end.x) * tan(ra));
	}
	else if (ra < NORTH || ra > SOUTH)
	{
		v.end.x = g->p.x + (g->mm.block_size -(g->p.x % g->mm.block_size));
		v.end.y = ((g->p.x - v.end.x) * tan(ra)) + g->p.y;
	}
	return (v);
}

int	get_infinite(t_global *g, double ra, int flag)
{
	if (flag == 0)
	{
		if (ra == EAST || ra == WEST)
			return (ft_max(g->m.rows, g->m.cols));
		else
			return (0);
	}
	else
	{
		if (ra == SOUTH || ra == NORTH)
			return (ft_max(g->m.rows, g->m.cols));
		else
			return (0);
	}
}
