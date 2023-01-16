/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_prepend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:38:42 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:46:32 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

void	ps_prepend(t_global *g, t_tab *tab, int value)
{
	int	i;
	int	j;
	int	*res;

	i = 1;
	j = 0;
	tab->size += 1;
	res = malloc(sizeof(int) * tab->size);
	if (!res)
		free_everything_and_exit(g);
	res[0] = value;
	while (j < tab->size - 1)
		res[i++] = tab->data[j++];
	free(tab->data);
	tab->data = res;
	return ;
}
