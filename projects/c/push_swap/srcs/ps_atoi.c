/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:22:55 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/08 19:46:19 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pushswap.h"

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

static void	process_pre_data(const char *str, int *i, int *sign)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || (str[*i] == 32))
		*i += 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -(*sign);
		*i += 1;
	}
	while (str[*i] == '0')
		*i += 1;
}

static void	convert(const char *str, int *atoi, int *i, int *number_count)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*atoi = *atoi * 10 + str[*i] - 48;
		*number_count += 1;
		*i += 1;
	}
}

int	ps_atoi(const char *str, t_global *g)
{
	int	atoi;
	int	sign;
	int	number_count;
	int	i;

	i = 0;
	number_count = 0;
	sign = 1;
	atoi = 0;
	process_pre_data(str, &i, &sign);
	convert(str, &atoi, &i, &number_count);
	if (str[i] != 0)
		free_everything_and_exit(g);
	i = ft_count_numbers(atoi);
	if (i == number_count)
	{
		if (atoi > -1)
			return (atoi * sign);
		if (atoi == -2147483648 && sign == -1)
			return (atoi);
	}
	free_everything_and_exit(g);
	return (0);
}
