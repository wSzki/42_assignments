/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 03:25:00 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/22 13:14:46 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	thread_create_and_detach(t_data *d, int i)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, routine, &(d->p[i])))
		error(d, THREAD);
	pthread_detach(thread);
	usleep(10);
}

void	threads(t_data *d)
{
	int			i;
	pthread_t	thread;

	d->t_start = timestamp();
	i = -1;
	while (++i < d->nb_philos)
		if (i % 2 == 0)
			thread_create_and_detach(d, i);
	usleep(100);
	i = -1;
	while (++i < d->nb_philos)
		if (i % 2 == 1)
			thread_create_and_detach(d, i);
	pthread_create(&thread, NULL, &monitor_death, &d);
	pthread_join(thread, NULL);
}
