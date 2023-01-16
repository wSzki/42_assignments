/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:48:51 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/09 16:56:38 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static void	normalise_list(t_global *g)
{
	while (g->a->size % 4 != 0)
	{
		scroll_to(g, g->a, find_largest(g->a));
		px(g, B_ID);
	}
}

void	sort(t_global *g, int lowest_sorted)
{
	int		median_a;
	int		median_b;
	int		median_c;
	long	minimum;

	check_simple_cases(g);
	normalise_list(g);
	find_median(g->a, &median_a, find_smallest(g->a), find_largest(g->a));
	find_median(g->a, &median_b, find_smallest(g->a), median_a);
	find_median(g->a, &median_c, median_a, find_largest(g->a));
	minimum = (long)find_smallest(g->a) - 1;
	lowest_sorted = quarter_sort(g, median_c, find_largest(g->a), NO_VALUE);
	lowest_sorted = quarter_sort(g, median_a, median_c, lowest_sorted);
	lowest_sorted = quarter_sort(g, median_b, median_a, lowest_sorted);
	lowest_sorted = quarter_sort(g, minimum, median_b, lowest_sorted);
	scroll_to(g, g->a, find_smallest(g->a));
}
