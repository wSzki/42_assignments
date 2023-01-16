/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:40:33 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/25 22:18:25 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_print_sign(long n, t_flags *flags)
{
	if (flags->id == 'p')
	{
		ft_putchar_inc('0', flags);
		ft_putchar_inc('x', flags);
	}
	else if (n < 0)
		ft_putchar_inc('-', flags);
	return ;
}

static int	ft_process_flags(long n, int nb_chars, t_flags *flags)
{
	int fill;
	int two_spaces_if_p;

	fill = 0;
	two_spaces_if_p = 0;
	if (flags->id == 'p')
		two_spaces_if_p = 2;
	if (flags->width || flags->left || flags->zero)
		fill = flags->width + flags->left + flags->zero;
	if (fill && flags->precision >= 0)
	{
		if (flags->precision >= nb_chars)
		{
			fill = fill - flags->precision - (n < 0);
			flags->precision -= nb_chars;
			flags->precision += two_spaces_if_p + (n < 0);
			return (fill);
		}
		flags->precision = 0;
	}
	else if (flags->precision)
		flags->precision = flags->precision - nb_chars + (n < 0);
	if (n == 0 && flags->id == 'p')
		fill -= two_spaces_if_p;
	return (fill - nb_chars);
}

static void	print_processed_flags(long n, int fill, t_flags *flags)
{
	if (fill || (flags->precision))
	{
		if (flags->width)
			ft_fill_zero_space(fill, ' ', flags);
		ft_print_sign(n, flags);
		if (flags->precision)
			ft_fill_zero_space(flags->precision, '0', flags);
		if (flags->zero)
			ft_fill_zero_space(fill, '0', flags);
		ft_putnbr_base_inc(n, flags);
		if (flags->left)
			ft_fill_zero_space(fill, ' ', flags);
	}
	else
	{
		if (flags->id == 'p' && n == 0)
		{
			ft_putchar_inc('0', flags);
			ft_putchar_inc('x', flags);
			ft_putchar_inc('0', flags);
			return ;
		}
		ft_print_sign(n, flags);
		ft_putnbr_base_inc(n, flags);
	}
}

void		ft_printf_number(long n, t_flags *flags)
{
	int fill;

	if (((flags->zero) && ((flags->precision > 0) || (flags->precision == -1))))
	{
		flags->width = flags->zero;
		flags->zero = 0;
	}
	if (n == 0 && flags->precision == -1)
	{
		fill = flags->width + flags->left;
		if (flags->id == 'p')
			fill -= 2;
		if (flags->width)
			ft_fill_zero_space(fill, ' ', flags);
		if (flags->id == 'p')
			ft_print_sign(n, flags);
		if (flags->left)
			ft_fill_zero_space(fill, ' ', flags);
		return ;
	}
	fill = ft_process_flags(n, ft_count_digits(n, flags), flags);
	print_processed_flags(n, fill, flags);
	return ;
}
