/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_largest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:26:25 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:41:26 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

int	find_largest(t_tab *tab)
{
	int	i;
	int	largest;

	if (tab->size == 0)
		return (0);
	largest = tab->data[0];
	i = 0;
	while (++i < tab->size)
		if (tab->data[i] > largest)
			largest = tab->data[i];
	return (largest);
}
