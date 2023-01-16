/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_smallest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:26:01 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:39:51 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

int	find_smallest(t_tab *tab)
{
	int	i;
	int	smallest;

	if (tab->size == 0)
		return (0);
	smallest = tab->data[0];
	i = 0;
	while (++i < tab->size)
		if (tab->data[i] < smallest)
			smallest = tab->data[i];
	return (smallest);
}
