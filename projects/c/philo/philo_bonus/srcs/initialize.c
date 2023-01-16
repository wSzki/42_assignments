/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:20:55 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/21 18:52:44 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <semaphore.h>

static void	init_data(t_data *d, int ac, char **av)
{
	d->nb_philos = ft_atoi(d, av[1]);
	d->t_die = ft_atoi(d, av[2]);
	d->t_eat = ft_atoi(d, av[3]);
	d->t_sleep = ft_atoi(d, av[4]);
	d->everybody_ate = NO;
	d->somebody_died = NO;
	d->p = NULL;
	d->forks = NULL;
	d->n_meals = UNUSED;
	if (ac == 6)
		d->n_meals = ft_atoi(d, av[5]);
	if (d->nb_philos == 0)
		error(d, NO_PHILO);
}

static void	init_philosophers(t_data *d)
{
	int	i;

	d->p = malloc(sizeof(t_philo) * d->nb_philos);
	if (d->p == NULL)
		error(d, MEMORY);
	i = -1;
	while (++i < d->nb_philos)
	{
		d->p[i].d = d;
		d->p[i].meals_eaten = 0;
		d->p[i].last_meal = 0;
		d->p[i].id = i + 1;
		d->p[i].left_fork = i;
		d->p[i].right_fork = i + 1;
		if (i == d->nb_philos - 1)
			d->p[i].right_fork = 0;
	}
}

static void	init_semaphore(t_data *d)
{
	sem_unlink("message");
	sem_unlink("forks");
	d->forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR, d->nb_philos);
	d->message = sem_open("message", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (d->forks == SEM_FAILED || d->message == SEM_FAILED)
		error(d, SEM_ERROR);
}

void	initialize(t_data **data, int ac, char **av)
{
	t_data	*d;

	d = malloc(sizeof(*d));
	if (d == NULL)
		error(NULL, MEMORY);
	init_data(d, ac, av);
	init_philosophers(d);
	init_semaphore(d);
	*data = d;
}
