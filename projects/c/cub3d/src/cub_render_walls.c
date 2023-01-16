/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_render_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 03:55:32 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/02 18:34:34 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define NORD 0x007C9C90
#define SUD 0x00a9b665

#define OUEST  0x00fabd2f
#define EST  0x00ea6962

static double	get_dist(t_vector v, double ray_angle)
{
	int	x;
	int	y;

	x = v.end.x - v.start.x;
	y = v.end.y - v.start.y;
	x = x * x;
	y = y * y;
	return ((sqrtf(x + y)) * cos(M_PI / 180.0 * ray_angle));
}

static double	get_wall_size(double dist, t_global *g)
{
	double	projected_wall_size;
	double	distance_proj_plane;

	distance_proj_plane = (WIDTH * 0.5) / (M_PI / 180.0 * 30.0);
	projected_wall_size = g->mm.block_size / dist * distance_proj_plane;
	return (projected_wall_size);
}

t_img	cub_get_texture_and_offsets(t_global *g, t_vector vector)
{
	float	virgule;

	virgule = (int)vector.end.x % (int)g->mm.block_size;
	if (g->wall.color == NORD)
	{
		g->wall.offset_x = (virgule / g->mm.block_size) * g->x.north.width;
		return (g->x.north);
	}
	else if (g->wall.color == SUD)
	{
		g->wall.offset_x = (virgule / g->mm.block_size) * g->x.south.width;
		return (g->x.south);
	}
	virgule = (int)vector.end.y % (int)g->mm.block_size;
	if (g->wall.color == EST)
	{
		g->wall.offset_x = (virgule / g->mm.block_size) * g->x.east.width;
		return (g->x.east);
	}
	else if (g->wall.color == OUEST)
	{
		g->wall.offset_x = (virgule / g->mm.block_size) * g->x.west.width;
		return (g->x.west);
	}
	return (g->x.north);
}

static void	cub_render_vertical_line(\
		t_global *g, t_vector vector, int v_ray, double ray_angle)
{
	int				head;
	unsigned int	pixel;
	t_img			current_texture;

	head = 0;
	pixel = 0;
	g->wall.offset_x = 0;
	g->wall.offset_y = 0;
	g->wall.size = get_wall_size(get_dist(vector, ray_angle), g);
	g->wall.start = (HEIGHT - g->wall.size) * 0.5;
	g->wall.end = g->wall.start + g->wall.size;
	current_texture = cub_get_texture_and_offsets(g, vector);
	while (head < g->wall.start)
		cub_put_pixel(&g->x.buffer, v_ray, head++, g->d.c);
	while (head < g->wall.end && head < HEIGHT)
	{
		g->wall.offset_y = (head - g->wall.start) * \
						((double)current_texture.height / (double)g->wall.size);
		pixel = cub_get_pixel(\
				&current_texture, g->wall.offset_x, g->wall.offset_y);
		cub_put_pixel(&g->x.buffer, v_ray, head, pixel);
		head++;
	}
	while (head < HEIGHT)
		cub_put_pixel(&g->x.buffer, v_ray, head++, g->d.f);
}

void	cub_render_walls(t_global *g)
{
	int				v_ray;
	t_vector		vector;
	double			ray_angle;
	double			angle_increment;

	g->wall.color = 0;
	v_ray = WIDTH;
	vector.start.x = g->p.x;
	vector.start.y = g->p.y;
	ray_angle = -VIEW_ANGLE_OFFSET;
	angle_increment = VIEW_RANGE / WIDTH;
	while (ray_angle <= VIEW_ANGLE_OFFSET)
	{
		vector.end = cub_get_wall_pos(\
				g, vector, g->p.angle - ray_angle, &g->wall.color);
		cub_render_vertical_line(g, vector, v_ray, ray_angle);
		ray_angle += angle_increment;
		v_ray--;
	}
}
