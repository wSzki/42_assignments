/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:03:20 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/22 23:04:09 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_atoi_count_numbers(int n)
{
	size_t i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int			ft_printf_atoi(const char *str)
{
	long int	atoi;
	int			np;
	int			j;
	int			i;

	i = 0;
	j = 0;
	np = 1;
	atoi = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			np = -np;
	while (str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && j++ >= 0)
		atoi = atoi * 10 + str[i++] - 48;
	i = ft_atoi_count_numbers(atoi);
	if (i == j)
		return (atoi * np);
	if (np < 0)
		return (0);
	return (-1);
}
