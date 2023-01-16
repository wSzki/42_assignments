/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:26:23 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:43:18 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

void	find_median(t_tab *tab, int *median, int min_value, int max_value)
{
	int	i;
	int	j;
	int	count;
	int	target;

	count = 0;
	i = -1;
	while (++i < tab->size)
	{
		j = -1;
		count = 0;
		target = tab->data[i];
		while (++j < tab->size)
		{
			if (tab->data[j] < target && tab->data[j] > min_value)
				count--;
			if (tab->data[j] > target && tab->data[j] < max_value)
				count++;
		}
		if (count == 0 || count == 1 )
		{
			*median = tab->data[i];
			return ;
		}
	}
}
