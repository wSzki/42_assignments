/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:45:00 by wszurkow          #+#    #+#             */
/*   Updated: 2020/10/06 14:29:52 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int			i;
	char		*res;
	long int	long_n;

	long_n = n;
	i = ft_count_digits(n);
	if (n <= 0)
		i++;
	if (!(res = (char *)malloc(sizeof(char) * i + 1)))
		return (0);
	res[i] = '\0';
	if (long_n < 0)
	{
		long_n = -long_n;
		res[0] = '-';
	}
	i--;
	while (i >= 0 + (res[0] == '-'))
	{
		res[i] = long_n % 10 + 48;
		long_n = long_n / 10;
		i--;
	}
	return (res);
}
