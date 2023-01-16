/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_angle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:45:42 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/01 17:56:09 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_init_angle(t_global *g, char dir)
{
	if (dir == 'S')
		g->p.angle = 90;
	else if (dir == 'N')
		g->p.angle = -90;
	else if (dir == 'E')
		g->p.angle = 0;
	else
		g->p.angle = 180;
}
