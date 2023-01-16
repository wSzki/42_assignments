/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 03:30:48 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/14 21:31:37 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	putmsg(t_data *d, t_philo *p, int msg_no)
{
	long long	current_time;

	sem_wait(d->message);
	current_time = timestamp() - d->t_start;
	if (msg_no == LEFT_FORK)
		printf("%lli %d has taken a fork (left)\n", current_time, p->id);
	else if (msg_no == RIGHT_FORK)
		printf("%lli %d has taken a fork (right)\n", current_time, p->id);
	else if (msg_no == EATING)
		printf("%lli %d is eating\n", current_time, p->id);
	else if (msg_no == SLEEPING)
		printf("%lli %d is sleeping\n", current_time, p->id);
	else if (msg_no == THINKING)
		printf("%lli %d is thinking\n", current_time, p->id);
	else if (msg_no == DEATH)
		printf("%lli %d died\n", current_time, p->id);
	else if (msg_no == END)
		printf("%lli [ END ]\n", current_time);
	sem_post(d->message);
}
