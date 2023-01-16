/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 20:29:27 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:37:54 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static void	sub_rr(t_tab *tab)
{
	int	tmp;
	int	tmp_size;

	if (tab)
	{
		if (tab->size > 1)
		{
			tmp = tab->data[tab->size - 1];
			tmp_size = tab->size;
			while (tmp_size > 0)
			{
				tab->data[tmp_size] = tab->data[tmp_size - 1];
				tmp_size--;
			}
			tab->data[0] = tmp;
		}
	}
	return ;
}

void	rrx(t_global *g, int id)
{
	if (id == A_ID)
	{
		if (g->a->size > 1)
		{
			sub_rr(g->a);
			write(1, "rra\n", 4);
		}
	}
	if (id == B_ID)
	{
		if (g->b->size > 1)
		{
			sub_rr(g->b);
			write(1, "rrb\n", 4);
		}
	}
	if (id == R_ID)
	{
		sub_rr(g->a);
		sub_rr(g->b);
		write(1, "rrr\n", 4);
	}
}
