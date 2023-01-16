/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 01:02:26 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/19 17:17:54 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	mt_black_magic(pid_t pid_child)
{
	if (kill(pid_child, SIGUSR1) != 0)
		mt_print_exit("Signal error");
}

static int	mt_catch_end(pid_t pid_child, int signal, int zero_count)
{
	if (zero_count == 3 && signal == SIGUSR2)
	{
		write(1, "\n", 1);
		if (kill(pid_child, SIGUSR2) != 0)
			mt_print_exit("Signal error");
		return (1);
	}
	return (0);
}

static unsigned char	mt_process_ticks(\
		unsigned char *c, \
		int *ticks, \
		int *zero_count, \
		pid_t pid_child)
{
	if (*zero_count == 0)
	{
		*c = *c + (*ticks - 1) * 100;
		*ticks = 0;
		*zero_count += 1;
		return (0);
	}
	else if (*zero_count == 1)
	{
		*c = *c + (*ticks - 1) * 10;
		*ticks = 0;
		*zero_count += 1;
		return (0);
	}
	else if (*zero_count == 2)
	{
		*c = *c + (*ticks - 1);
		write(1, c, 1);
		*c = 0;
		*ticks = 0;
		*zero_count += 1;
		mt_black_magic(pid_child);
		return (1);
	}
	return (0);
}

static void	mt_receive(int signal, siginfo_t *siginfo, void *unused)
{
	static int				ticks;
	static int				zero_count;
	static pid_t			pid_child;
	static unsigned char	c;

	(void)unused;
	if (pid_child != siginfo->si_pid)
	{
		pid_child = siginfo->si_pid;
		ticks = 0;
		zero_count = 0;
		c = 0;
	}
	if (mt_catch_end(pid_child, signal, zero_count))
		return ;
	if (zero_count >= 3)
		zero_count = 0;
	if (signal == SIGUSR1)
		ticks++;
	if (signal == SIGUSR2)
		if (mt_process_ticks(&c, &ticks, &zero_count, pid_child) == 1)
			return ;
	mt_black_magic(pid_child);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	mt_print_pid(ac);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = mt_receive;
	if ((sigaction(SIGUSR1, &sa, NULL)) != 0)
		mt_print_exit("Sigaction error\n");
	if ((sigaction(SIGUSR2, &sa, NULL)) != 0)
		mt_print_exit("Sigaction error\n");
	while (1)
	{
		pause();
		usleep(1000);
	}
	return (0);
}
