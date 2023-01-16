/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:19:26 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/15 22:45:02 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define NO           0
# define YES          1
# define STOP         0
# define CONTINUE     1

// MESSAGE CODES
# define LEFT_FORK    0
# define RIGHT_FORK   1
# define EATING       2
# define SLEEPING     3
# define THINKING     4
# define DEATH        5

// ERROR CODES
# define UNUSED      -2
# define ERROR       -1
# define OK           0
# define MEMORY       1
# define ARG_NON_NUM  2
# define OVERFLOW     3
# define NO_PHILO     4
# define ARG_NB       5
# define MUTEX        6
# define THREAD       7
# define END          8

typedef struct s_philo
{
	struct s_data	*d;
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal;
}	t_philo;

typedef struct s_data
{
	struct s_philo	*p;
	int				nb_philos;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				n_meals;
	int				everybody_ate;
	int				somebody_died;
	long long		t_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
}	t_data;

// LIBFT
int			ft_atoi(t_data *d, const char *str);
size_t		ft_strlen(const char *str);

// UTILS
void		initialize(t_data **data, int ac, char **av);
long long	timestamp(void);
void		putmsg(t_data *d, t_philo *p, int msg_no);
int			all_full(t_data *d);

// ERROR MANAGEMENT
void		error(t_data *d, int errno);

// MEMORY
void		free_data(t_data *d);

// CORE
void		threads(t_data *d);
void		*monitor_death(void *ptr);
void		*routine(void *ptr);
#endif
