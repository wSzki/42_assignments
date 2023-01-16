/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_vector_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:44:37 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/01 00:33:02 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	cub_vector_end(t_coord start, double len, double angle)
{
	t_coord	end;
	double	radians;

	radians = (M_PI / 180) * (double)angle;
	end.x = roundf(start.x + (len * cos(radians)));
	end.y = roundf(start.y + (len * sin(radians)));
	return (end);
}
