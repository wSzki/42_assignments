/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:01:04 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:45:01 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

void	sort_three(t_global*g, int *tab)
{
	if (tab[0] > tab[1] && tab[1] < tab[2])
		sx(g, A_ID);
	if (tab[0] > tab[1] && tab[1] > tab[2])
	{
		sx(g, A_ID);
		rrx(g, A_ID);
	}
	if (tab[0] > tab[1] && tab[1] < tab[2])
		rx(g, A_ID);
	if (tab[1] > tab[0] && tab[1] > tab[2] && tab[2] > tab[0])
	{
		sx(g, A_ID);
		rx(g, A_ID);
	}
	if (tab[1] > tab[0] && tab[1] > tab[2] && tab[2] < tab[0])
		rrx(g, A_ID);
}
