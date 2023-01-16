/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_fill_tab_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:43:19 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:46:44 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

static void	check_duplicates(t_global *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->a->size)
	{
		j = i + 1;
		while (j < g->a->size)
		{
			if (g->a->data[i] == g->a->data[j])
				free_everything_and_exit(g);
			j++;
		}
		i++;
	}
}

void	fill_tab_a(t_global *g, int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		g->a->data[j] = ps_atoi(av[i], g);
		j++;
		i++;
	}
	check_duplicates(g);
}
