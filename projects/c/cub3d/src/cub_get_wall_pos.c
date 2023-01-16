/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_wall_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 03:53:31 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/28 16:31:32 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_position(t_global *g, double vx, double vy)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = vx / g->mm.block_size;
	y = vy / g->mm.block_size;
	i = 0;
	while (g->m.map[i])
	{
		j = 0;
		if (i == y)
		{
			while (g->m.map[i][j])
			{
				if (j == x)
					return (g->m.map[i][j] == '1');
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	cub_get_col(t_global *g, unsigned int *col, int x_or_y, int dir)
{
	int				d;
	int				offset;
	int				b;
	unsigned int	wall_col;

	b = g->mm.block_size;
	d = dir;
	offset = d % 2;
	if (d == N)
		wall_col = GREEN;
	if (d == S)
		wall_col = BLUE;
	if (d == E)
		wall_col = YELLOW;
	if (d == W)
		wall_col = RED;
	if ((x_or_y + offset) % b == 0)
		*col = wall_col;
}

static t_coord	cub_get_wall_pos_hor(t_global *g, t_vector v, double ray)
{
	int		dof;
	double	ra;
	double	xo;
	double	yo;

	ra = cub_normalize(ray) * PI / 180.0;
	yo = g->mm.block_size;
	dof = get_infinite(g, ra, 0);
	v = get_first_out_h(g, v, ra);
	if (ra > WEST && ra < EAST)
		yo *= -1;
	xo = (-yo) * (1 / tan(ra));
	while (dof < ft_max(g->m.rows, g->m.cols))
	{
		if (check_position(g, v.end.x, v.end.y))
			return (v.end);
		else
		{
			v.end.x += xo;
			v.end.y += yo;
			dof++;
		}
	}
	return (v.start);
}

static t_coord	cub_get_wall_pos_ver(t_global *g, t_vector v, double ray)
{
	int		dof;
	double	ra;
	double	xo;
	double	yo;

	ra = cub_normalize(ray) * PI / 180.0;
	xo = g->mm.block_size;
	dof = get_infinite(g, ra, 1);
	v = get_first_out_v(g, v, ra);
	if (ra > NORTH && ra < SOUTH)
		xo *= -1;
	yo = (-xo) * tan(ra);
	while (dof < ft_max(g->m.rows, g->m.cols))
	{
		if (check_position(g, v.end.x, v.end.y))
			return (v.end);
		else
		{
			v.end.x += xo;
			v.end.y += yo;
			dof++;
		}
	}
	return (v.start);
}

t_coord	cub_get_wall_pos(t_global *g, t_vector v, double ray, unsigned int *col)
{
	double		dist_h;
	double		dist_v;
	t_vector	hor;
	t_vector	ver;

	*col = 0;
	hor.end = cub_get_wall_pos_hor(g, v, ray);
	ver.end = cub_get_wall_pos_ver(g, v, ray);
	dist_h = cub_get_axis_dist(v, hor.end);
	dist_v = cub_get_axis_dist(v, ver.end);
	if (dist_v == 0 || (dist_h != 0 && dist_h <= dist_v))
	{
		v.end = hor.end;
		cub_get_col(g, col, hor.end.y, N);
		cub_get_col(g, col, hor.end.y, S);
	}
	else
	{
		v.end = ver.end;
		cub_get_col(g, col, ver.end.x, E);
		cub_get_col(g, col, ver.end.x, W);
	}
	return (v.end);
}
