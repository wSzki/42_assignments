/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:59:36 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/20 21:34:53 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	cub_get_pixel(t_img *img, int w, int h)
{
	char			*addr;
	unsigned int	offset;
	unsigned int	w_offset;
	unsigned int	h_offset;

	w_offset = h * (img->line_len);
	h_offset = w * (img->bits_per_px / 8);
	offset = w_offset + h_offset;
	addr = img->addr + offset;
	return (*(unsigned int *)addr);
}
