/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 03:20:35 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/22 13:29:35 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	better_usleep(long long duration)
{
	long long	start;
	long long	current;

	start = timestamp();
	current = start;
	while (current - start < duration)
	{
		usleep(1);
		current = timestamp();
	}
}

static int	eat(t_data *d, t_philo *p)
{
	if (sem_wait(d->forks) == ERROR)
		error(d, SEM_ERROR);
	if (d->somebody_died || all_full(d))
		return (STOP);
	putmsg(d, p, LEFT_FORK);
	if (sem_wait(d->forks) == ERROR)
		error(d, SEM_ERROR);
	if (d->somebody_died || all_full(d))
		return (STOP);
	putmsg(d, p, RIGHT_FORK);
	putmsg(d, p, EATING);
	p->last_meal = timestamp();
	p->meals_eaten += 1;
	usleep(d->t_eat * 1000);
	if (sem_post(d->forks) == ERROR)
		error(d, SEM_ERROR);
	if (sem_post(d->forks) == ERROR)
		error(d, SEM_ERROR);
	if (d->somebody_died == YES || all_full(d) == YES)
		return (STOP);
	return (CONTINUE);
}

static int	nap(t_data *d, t_philo *p)
{
	putmsg(d, p, SLEEPING);
	better_usleep(d->t_sleep);
	if (d->somebody_died == YES || all_full(d) == YES)
		return (STOP);
	return (CONTINUE);
}

static int	think(t_data *d, t_philo *p)
{
	putmsg(d, p, THINKING);
	if (d->somebody_died == YES || all_full(d) == YES)
		return (STOP);
	return (CONTINUE);
}

void	*routine(void *ptr)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)ptr;
	d = p->d;
	while (d->somebody_died == NO || all_full(d) == NO)
	{
		if (eat(d, p) == STOP)
			break ;
		if (nap(d, p) == STOP)
			break ;
		if (think(d, p) == STOP)
			break ;
		if ((d->t_die % (d->t_eat + d->t_sleep)) == 0)
			usleep(1000);
		else
			usleep(100);
	}
	return (NULL);
}
