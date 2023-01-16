/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_to.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 20:57:27 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:42:48 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

static int	count_steps_to(t_tab *tab, int target)
{
	int	i;

	i = 0;
	while (i < tab->size)
	{
		if (tab->data[i] == target)
			break ;
		i++;
	}
	if (i < tab->size / 2)
		return (i);
	return ((tab->size - i) * -1);
}

void	scroll_to(t_global *g, t_tab *tab, int target_value)
{
	int	steps_to_target;

	if (tab->size > 1)
	{
		steps_to_target = count_steps_to(tab, target_value);
		while (tab->data[0] != target_value)
		{
			if (steps_to_target > 0)
				rx(g, tab->id);
			if (steps_to_target < 0)
				rrx(g, tab->id);
		}
	}
}
