/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:36:42 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/29 15:33:02 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_free_struct(t_global *g)
{
	int	i;

	i = 0;
	free(g->d.n);
	free(g->d.e);
	free(g->d.s);
	free(g->d.w);
	free(g->d.r);
	if (g->m.map)
		while (g->m.map[i] != NULL)
			free (g->m.map[i++]);
	free(g->m.map);
	free(g->line);
	i = 0;
	if (g->split)
	{
		while (g->split[i])
			free(g->split[i++]);
		free(g->split[i]);
	}
	free(g->split);
}

static void	cub_destroy_all_images(t_global *g)
{
	if (g->x.buffer.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.buffer.img);
	if (g->x.background.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.background.img);
	if (g->x.north.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.north.img);
	if (g->x.south.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.south.img);
	if (g->x.east.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.east.img);
	if (g->x.west.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.west.img);
	if (g->x.minimap.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.minimap.img);
	if (g->x.mm_floor.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.mm_floor.img);
	if (g->x.mm_wall.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.mm_wall.img);
	if (g->x.mm_player.img != NULL)
		mlx_destroy_image(g->x.mlx, g->x.mm_player.img);
}

static void	cub_free_mlx(t_global *g)
{
	if (g->x.mlx != NULL)
		cub_destroy_all_images(g);
	if (g->x.mlx != NULL && g->x.win != NULL)
		mlx_destroy_window(g->x.mlx, g->x.win);
	if (g->x.mlx != NULL)
	{
		mlx_destroy_display(g->x.mlx);
		free(g->x.mlx);
	}
}

void	cub_free_all(t_global *g)
{
	if (g == NULL)
		return ;
	cub_free_struct(g);
	cub_free_mlx(g);
	if (g->fd != -1)
		close(g->fd);
	free(g);
}
