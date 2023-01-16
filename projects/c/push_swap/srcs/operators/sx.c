/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 20:33:29 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:37:03 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static void	sub_s(t_tab *tab)
{
	int	tmp;

	if (tab)
	{
		if (tab->size > 1)
		{
			tmp = 0;
			tmp = tab->data[0];
			tab->data[0] = tab->data[1];
			tab->data[1] = tmp;
		}
	}
	return ;
}

void	sx(t_global *g, int id)
{
	if (id == A_ID)
	{
		if (g->a->size > 1)
		{
			sub_s(g->a);
			write(1, "sa\n", 3);
		}
	}
	if (id == B_ID)
	{
		if (g->b->size > 1)
		{
			sub_s(g->b);
			write(1, "sb\n", 3);
		}
	}
	if (id == R_ID)
	{
		sub_s(g->a);
		sub_s(g->b);
		write(1, "ss\n", 3);
	}
}
