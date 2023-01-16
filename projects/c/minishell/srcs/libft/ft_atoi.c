/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:17:50 by adlancel          #+#    #+#             */
/*   Updated: 2021/11/05 15:05:32 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_digits(long int n)
{
	int			i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*res;
	long int	long_n;
	int			is_neg;

	is_neg = 0;
	long_n = n;
	i = ft_count_digits(n) + (n <= 0);
	res = (char *)malloc(sizeof(char) * i + 1);
	if (res == NULL)
		return (0);
	res[i] = '\0';
	if (long_n < 0)
	{
		long_n = -long_n;
		res[0] = '-';
		is_neg = 1;
	}
	while (--i >= 0 + (is_neg))
	{
		res[i] = long_n % 10 + 48;
		long_n = long_n / 10;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			negative;
	long int	atoi;

	i = 0;
	j = 0;
	atoi = 0;
	negative = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			negative = -negative;
	while (str[i] == '0')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && j++ >= 0)
		atoi = atoi * 10 + str[i++] - '0';
	i = ft_count_digits(atoi);
	if (i == j)
		return (atoi * negative);
	if (negative < 0)
		return (0);
	return (-1);
}
