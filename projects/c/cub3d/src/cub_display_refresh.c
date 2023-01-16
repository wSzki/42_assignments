/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_display_refresh.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:48:00 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/25 19:57:44 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_minimap_put_player(t_global *g)
{
	cub_img_join(\
			&g->x.buffer, \
			&g->x.mm_player, \
			(g->p.x - g->mm.block_size / 2) / 4.0 + 2, \
			(g->p.y - g->mm.block_size / 2) / 4.0 + 2);
}

void	cub_display_refresh(t_global *g)
{
	cub_render_walls(g);
	cub_img_join(&g->x.buffer, &g->x.minimap, 0, 0);
	cub_minimap_put_player(g);
	mlx_put_image_to_window(g->x.mlx, g->x.win, g->x.buffer.img, 0, 0);
}
