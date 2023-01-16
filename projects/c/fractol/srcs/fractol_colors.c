/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:15:10 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/16 15:15:11 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	fractol_set_additional_colors(t_global *g)
{
	g->color[16] = 0x306082;
	g->color[17] = 0x5b6ee1;
	g->color[18] = 0x639bff;
	g->color[19] = 0x5fcde4;
	g->color[20] = 0xcbdbfc;
	g->color[21] = 0xffffff;
	g->color[22] = 0x9badb7;
	g->color[23] = 0x847e87;
	g->color[24] = 0x696a6a;
	g->color[25] = 0x595652;
	g->color[26] = 0x76428a;
	g->color[27] = 0xac3232;
	g->color[28] = 0xd95763;
	g->color[29] = 0xd77bba;
	g->color[30] = 0x8f974a;
	g->color[31] = 0x8a6f30;
}

void	fractol_set_color(t_global *g)
{
	g->color = malloc(sizeof(g->color) * 64);
	if (!g)
	{
		printf("Error\n%s", "*g malloc failed");
		free(g);
	}
	g->color[0] = 0x000000;
	g->color[1] = 0x222034;
	g->color[2] = 0x45283c;
	g->color[3] = 0x663931;
	g->color[4] = 0x8f563b;
	g->color[5] = 0xdf7126;
	g->color[6] = 0xd9a066;
	g->color[7] = 0xeec39a;
	g->color[8] = 0xfbf236;
	g->color[9] = 0x99e550;
	g->color[10] = 0x6abe30;
	g->color[11] = 0x37946e;
	g->color[12] = 0x4b692f;
	g->color[13] = 0x524b24;
	g->color[14] = 0x323c39;
	g->color[15] = 0x3f3f74;
	fractol_set_additional_colors(g);
}
