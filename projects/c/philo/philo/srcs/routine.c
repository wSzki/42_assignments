/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 03:20:35 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/22 13:27:43 by wszurkow         ###   ########.fr       */
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
	pthread_mutex_lock(&(d->forks[p->left_fork]));
	if (d->somebody_died || all_full(d))
		return (STOP);
	putmsg(d, p, LEFT_FORK);
	pthread_mutex_lock(&(d->forks[p->right_fork]));
	if (d->somebody_died || all_full(d))
		return (STOP);
	putmsg(d, p, RIGHT_FORK);
	putmsg(d, p, EATING);
	if (d->somebody_died || all_full(d))
		return (STOP);
	p->last_meal = timestamp();
	p->meals_eaten += 1;
	better_usleep(d->t_eat);
	pthread_mutex_unlock(&(d->forks[p->right_fork]));
	pthread_mutex_unlock(&(d->forks[p->left_fork]));
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
