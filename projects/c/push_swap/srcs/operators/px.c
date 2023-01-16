/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 20:19:09 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:38:23 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

void	px(t_global *g, int id)
{
	if (id == A_ID)
	{
		if (g->b)
		{
			if (g->b->size > 0)
			{
				ps_prepend(g, g->a, g->b->data[0]);
				ps_delete_first(g, g->b);
				write(1, "pa\n", 3);
			}
		}
	}
	if (id == B_ID)
	{
		if (g->a)
		{
			if (g->a->size > 0)
			{
				ps_prepend(g, g->b, g->a->data[0]);
				ps_delete_first(g, g->a);
				write(1, "pb\n", 3);
			}
		}
	}
}
