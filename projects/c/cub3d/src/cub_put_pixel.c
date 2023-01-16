/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_put_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:47:59 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/20 21:34:59 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// dst is the adress of the pixel to colorize
// int offset = (y * line_length + x * (bits_per_pixel / 8));
void	cub_put_pixel(t_img *img, int w, int h, unsigned int color)
{
	char	*addr;
	int		offset;
	int		w_offset;
	int		h_offset;

	h_offset = h * img->line_len;
	w_offset = w * (img->bits_per_px / 8);
	offset = w_offset + h_offset;
	addr = img->addr + offset;
	*(unsigned int *)addr = color;
}
