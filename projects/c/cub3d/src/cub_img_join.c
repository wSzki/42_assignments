/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_img_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:33:27 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/20 21:36:03 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_img_join(t_img *dest, t_img *src, int w_offset, int h_offset)
{
	int				w;
	int				h;
	unsigned int	pixel;

	w = 0;
	h = 0;
	while (h < src->height)
	{
		w = 0;
		while (w < src->width)
		{
			pixel = cub_get_pixel(src, w, h);
			cub_put_pixel(dest, w + w_offset, h + h_offset, pixel);
			w++;
		}
		h++;
	}
}
