/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simple_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:03:15 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/09 16:57:00 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static void	if_three_sort_exit(t_global *g)
{
	int	*tab;

	tab = g->a->data;
	if (g->a->size == 3)
	{
		if (tab[0] > tab[1] && tab[1] < tab[2])
			sx(g, A_ID);
		if (tab[0] > tab[1] && tab[1] > tab[2])
		{
			sx(g, A_ID);
			rrx(g, A_ID);
		}
		if (tab[0] > tab[1] && tab[1] < tab[2])
			rx(g, A_ID);
		if (tab[1] > tab[0] && tab[1] > tab[2] && tab[2] > tab[0])
		{
			sx(g, A_ID);
			rx(g, A_ID);
		}
		if (tab[1] > tab[0] && tab[1] > tab[2] && tab[2] < tab[0])
			rrx(g, A_ID);
		free_everything(g);
		exit(0);
	}
}

static void	if_two_sort_exit(t_global *g)
{
	if (g->a->size == 2)
	{
		if (g->a->data[0] > g->a->data[1])
			sx(g, A_ID);
		free_everything(g);
		exit(0);
	}
}

static void	if_a_sorted_exit(t_global *g)
{
	int	i;

	i = 1;
	while (i < g->a->size)
	{
		if (g->a->data[i] < g->a->data[i - 1])
			break ;
		i++;
	}
	if (i == g->a->size)
	{
		free_everything(g);
		exit(0);
	}
}

static void	if_five_sort_exit(t_global *g)
{
	if (g->a->size <= 10)
	{
		while (g->a->size > 3)
		{
			scroll_to(g, g->a, find_smallest(g->a));
			px(g, B_ID);
		}
		sort_three(g, g->a->data);
		while (g->b->size > 0)
			push_smallest_or_largest(g);
		free_everything(g);
		exit(0);
	}
}

void	check_simple_cases(t_global *g)
{
	if_a_sorted_exit(g);
	if_two_sort_exit(g);
	if_three_sort_exit(g);
	if_five_sort_exit(g);
}
