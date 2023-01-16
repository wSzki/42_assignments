/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:17:31 by adlancel          #+#    #+#             */
/*   Updated: 2022/04/28 17:02:26 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
