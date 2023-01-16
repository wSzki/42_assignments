/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_wall_pos_utils_bis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 03:53:31 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/28 16:32:47 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

double	cub_normalize(double angle)
{
	angle = CIRCLE - angle;
	if (angle > CIRCLE)
		angle -= CIRCLE;
	if (angle < 0)
		angle += CIRCLE;
	return (angle);
}

double	cub_get_axis_dist(t_vector v, t_coord end)
{
	double	a;
	double	b;

	if (end.x == v.start.x)
		return (0);
	a = ((end.x - v.start.x));
	b = ((end.y - v.start.y));
	return (sqrtf(a * a + b * b));
}
