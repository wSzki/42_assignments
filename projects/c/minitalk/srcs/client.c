/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 00:45:02 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/19 00:51:25 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	mt_confirm_reception(int signal, siginfo_t *siginfo, void *unused)
{
	(void) siginfo;
	(void) unused;
	if (signal == 12)
		mt_putstr("Server received the signal\n");
	return ;
}

static void	mt_black_magic(int signal, siginfo_t *siginfo, void *unused)
{
	(void)signal;
	(void)siginfo;
	(void)unused;
}

static void	mt_kill_usleep(pid_t pid, int signal, int time)
{
	if (kill(pid, signal) != 0)
		mt_print_exit("Signal error");
	usleep(time);
}

static void	mt_send_char(int pid, unsigned char c)
{
	int					usleep_time;
	unsigned char		ticks;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = mt_black_magic;
	if (sigaction(SIGUSR1, &sa, NULL) != 0)
		mt_print_exit("Sigaction error");
	usleep_time = 10000;
	ticks = c / 100 + 1;
	while (ticks-- > 0)
		mt_kill_usleep(pid, SIGUSR1, usleep_time);
	mt_kill_usleep(pid, SIGUSR2, usleep_time);
	ticks = c % 100 / 10 + 1;
	while (ticks-- > 0)
		mt_kill_usleep(pid, SIGUSR1, usleep_time);
	mt_kill_usleep(pid, SIGUSR2, usleep_time);
	ticks = c % 10 + 1;
	while (ticks-- > 0)
		mt_kill_usleep(pid, SIGUSR1, usleep_time);
	mt_kill_usleep(pid, SIGUSR2, usleep_time);
}

int	main(int ac, char **av)
{
	int					i;
	int					pid;
	unsigned char		*msg;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = mt_confirm_reception;
	if (sigaction(SIGUSR2, &sa, 0) != 0)
		mt_print_exit("Sigaction error");
	if (ac != 3)
		mt_print_exit("Requires 2 arguments : PID, message");
	pid = mt_atoi(av[1]);
	msg = (unsigned char *)av[2];
	i = -1;
	while (msg[++i])
		mt_send_char(pid, msg[i]);
	mt_kill_usleep(pid, SIGUSR2, 0);
	return (0);
}
