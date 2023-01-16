/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_smallest_or_largest.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:27:46 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/09 16:57:21 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static int	find_closest(t_global *g)
{
	int	i;
	int	smallest;
	int	largest;
	int	smallest_index;
	int	largest_index;

	i = 0;
	largest = find_largest(g->b);
	smallest = find_smallest(g->b);
	while (i < g->b->size)
	{
		if (g->b->data[i] == smallest)
			smallest_index = i;
		if (g->b->data[i] == largest)
			largest_index = i;
		i++;
	}
	if (smallest_index > g->b->size / 2)
		smallest_index = g->b->size - smallest_index;
	if (largest_index > g->b->size / 2)
		largest_index = g->b->size - largest_index;
	if (smallest_index < largest_index)
		return (0);
	return (1);
}

void	push_smallest_or_largest(t_global *g)
{
	int	closest;

	closest = find_closest(g);
	if (closest == 0)
	{
		scroll_to(g, g->b, find_smallest(g->b));
		px(g, A_ID);
		rx(g, A_ID);
	}
	else
	{
		scroll_to(g, g->b, find_largest(g->b));
		px(g, A_ID);
	}
}
