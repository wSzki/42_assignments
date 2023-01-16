/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:26:04 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:39:06 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pushswap.h"

void	free_everything(t_global *g)
{
	free(g->a->data);
	free(g->b->data);
	free(g->a);
	free(g->b);
	free(g);
}
