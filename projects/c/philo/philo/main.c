/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:17:27 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/15 22:59:43 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	free_data(t_data *d)
{
	int	i;

	if (d)
	{
		pthread_mutex_destroy(&(d->message));
		if (d->forks)
		{
			i = -1;
			while (++i < d->nb_philos)
				pthread_mutex_destroy(&(d->forks[i]));
			free(d->forks);
		}
		if (d->p)
			free(d->p);
		free(d);
	}
}

void	error(t_data *d, int errno)
{
	free_data(d);
	printf("\033[1;31mError\033[m\n");
	if (errno == ARG_NB)
		printf("Invalid number of arguments\n");
	if (errno == MEMORY)
		printf("Memory error\n");
	if (errno == ARG_NON_NUM)
		printf("Arguments must be positive numbers only\n");
	if (errno == OVERFLOW)
		printf("Argument int overflow\n");
	if (errno == NO_PHILO)
		printf("Number of philosophers cannot be 0\n");
	if (errno == MUTEX)
		printf("Mutex error\n");
	if (errno == THREAD)
		printf("Thread error\n");
	exit (1);
}

static void	wait_for_thread_cleanup(void)
{
	usleep(1000000);
}

int	main(int ac, char **av)
{
	t_data	*d;

	if (ac != 5 && ac != 6)
		error(NULL, ARG_NB);
	initialize(&d, ac, av);
	threads(d);
	wait_for_thread_cleanup();
	free_data(d);
	return (0);
}
