/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:01:59 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/21 17:00:57 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_init_img(t_global *g, t_img *img, int w, int h)
{
	img->img = NULL;
	img->addr = NULL;
	img->width = w;
	img->height = h;
	img->img = mlx_new_image(g->x.mlx, w, h);
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
