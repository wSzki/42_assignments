/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:52:38 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/23 00:49:20 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_count_digits(long n, t_flags *flags)
{
	int	i;
	int base_type;

	if (flags->id == 'd' || flags->id == 'i' || flags->id == 'u')
		base_type = 10;
	if (flags->id == 'x' || flags->id == 'X' || flags->id == 'p')
		base_type = 16;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		n = n / base_type;
		i++;
	}
	if (flags->id == 'p')
		return (i + 2);
	return (i);
}

void	ft_putchar_inc(int c, t_flags *flags)
{
	write(1, &c, 1);
	flags->written += 1;
}

int		is_in_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

void	ft_fill_zero_space(int flag, int c, t_flags *flags)
{
	while (flag > 0)
	{
		ft_putchar_inc(c, flags);
		flag--;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
