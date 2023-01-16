/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 01:49:38 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/19 01:49:38 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	mt_print_exit(char *str)
{
	mt_putstr("Error\n");
	mt_putstr(str);
	mt_putstr("\n");
	exit(1);
}

void	mt_print_pid(int ac)
{
	if (ac != 1)
		mt_print_exit("No parameters needed to launch the server");
	mt_putstr("Server started\n");
	mt_putstr("PID = ");
	mt_putnbr(getpid());
	mt_putstr("\n");
}

void	mt_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	mt_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = -n;
		}
		if (n > 9)
			mt_putnbr(n / 10);
		n = n % 10 + 48;
		write(1, &n, 1);
	}
}

int	mt_atoi(const char *str)
{
	long int	atoi;
	int			sign;
	int			j;
	int			i;

	i = 0;
	j = 0;
	sign = 1;
	atoi = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && j++ >= 0)
		atoi = atoi * 10 + str[i++] - 48;
	return (atoi * sign);
}
