/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quarter_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:29:00 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/09 16:57:51 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static int	find_closest_chunk(t_global *g, long smallest, long largest)
{
	int	i;

	i = 0;
	while (i < g->a->size / 2)
	{
		if (g->a->data[i] > smallest && g->a->data[i] <= largest)
			return (0);
		i++;
	}
	return (1);
}

int	quarter_sort(t_global *g, long smallest, long largest, long input)
{
	int	i;
	int	direction;
	int	offset;

	i = g->a->size + 1;
	offset = 0;
	while ((--i % 4) != 0)
		offset++;
	i = g->a->size - offset;
	while (g->a->size - offset > (i * 3) / 4)
	{
		direction = find_closest_chunk(g, smallest, largest);
		if (g->a->data[0] > smallest && g->a->data[0] <= largest)
			px(g, B_ID);
		else if (direction == 0)
			rx(g, A_ID);
		else if (direction == 1)
			rrx(g, A_ID);
	}
	if (input != NO_VALUE)
		scroll_to(g, g->a, input);
	i = find_smallest(g->b);
	while (g->b->size > 0)
		push_smallest_or_largest(g);
	return (i);
}
