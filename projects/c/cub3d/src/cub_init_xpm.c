/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_xpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:03:02 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/21 17:02:02 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_load_xpm(t_global *g, t_img *img, char *path)
{
	img->img = NULL;
	img->addr = NULL;
	img->img = mlx_xpm_file_to_image(\
			g->x.mlx, path, &img->width, &img->height);
	if (img->img == NULL)
		cub_error_str(g, MERR_MLX_IMG);
	img->addr = mlx_get_data_addr(\
			img->img, \
			&img->bits_per_px, \
			&img->line_len, \
			&img->endian);
	if (img->addr == NULL)
		cub_error_str(g, MERR_MLX_IMG);
}

void	cub_init_xpm(t_global **global)
{
	t_global	*g;

	g = *global;
	cub_load_xpm(g, &g->x.north, g->d.n);
	cub_load_xpm(g, &g->x.south, g->d.s);
	cub_load_xpm(g, &g->x.east, g->d.e);
	cub_load_xpm(g, &g->x.west, g->d.w);
}
