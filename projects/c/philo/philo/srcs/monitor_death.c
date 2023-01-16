/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 03:26:08 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/22 12:41:40 by wsz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	monitor(t_data *d, t_philo *p)
{
	int			i;
	long long	time;

	i = 0;
	time = 0;
	while (i < d->nb_philos && all_full(d) == NO)
	{
		if (d->p[i].last_meal == 0)
			d->p[i].last_meal = timestamp();
		time = timestamp() - d->p[i].last_meal;
		if (time > p->d->t_die)
		{
			p->d->somebody_died = YES;
			time = timestamp() - d->t_start;
			usleep(100000);
			printf("%lli %d died\n", time, d->p[i].id);
			return ;
		}
		if (++i == d->nb_philos)
			i = 0;
		usleep(1);
	}
}

void	*monitor_death(void *ptr)
{
	t_philo		*p;
	t_data		*d;

	p = (t_philo *)ptr;
	d = p->d;
	if (all_full(d) == NO)
		(monitor(d, p));
	return (NULL);
}
