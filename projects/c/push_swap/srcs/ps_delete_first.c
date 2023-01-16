/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_delete_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:40:00 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:45:58 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

void	ps_delete_first(t_global *g, t_tab *tab)
{
	int	i;
	int	j;
	int	*res;

	i = 1;
	j = 0;
	if (!tab)
		return ;
	if (!tab->size)
		return ;
	tab->size -= 1;
	if (tab->size == 0)
		return ;
	res = malloc(sizeof(int) * tab->size);
	if (!res)
		free_everything_and_exit(g);
	while (i < tab->size + 1)
	{
		res[j] = tab->data[i];
		i++;
		j++;
	}
	free(tab->data);
	tab->data = res;
	return ;
}
