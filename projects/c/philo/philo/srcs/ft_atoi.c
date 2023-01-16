/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 20:21:01 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/13 03:20:00 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_count_numbers(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_atoi(t_data *d, const char *str)
{
	int	atoi;
	int	j;
	int	i;

	i = 0;
	j = 0;
	atoi = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && j++ >= 0)
		atoi = atoi * 10 + str[i++] - 48;
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
		error(d, ARG_NON_NUM);
	i = ft_count_numbers(atoi);
	if (i != j)
		error(d, OVERFLOW);
	if (atoi < 0)
		error(d, OVERFLOW);
	return (atoi);
}
