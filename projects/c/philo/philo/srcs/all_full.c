/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_full.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 03:30:02 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/13 03:33:33 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	all_full(t_data *d)
{
	int	i;

	i = 0;
	if (d->n_meals == UNUSED)
		return (NO);
	while (i < d->nb_philos)
	{
		if (d->p[i].meals_eaten < d->n_meals)
			return (NO);
		i++;
	}
	d->somebody_died = 1;
	return (YES);
}
