/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:32:34 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/27 15:35:14 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	parse_wildcard(const char *fmt, t_flags *flags, va_list ap)
{
	int i;

	i = 0;
	if (fmt[i] == '*')
	{
		if (flags->precision == -1)
		{
			flags->precision = va_arg(ap, int);
			if (flags->precision == -1)
				flags->precision = -2;
		}
		else if (flags->left)
			flags->left = va_arg(ap, int);
		else if (flags->zero)
			flags->zero = va_arg(ap, int);
		else
			flags->width = va_arg(ap, int);
		return (1);
	}
	return (0);
}

static int	parse_flags(const char *fmt, t_flags *flags, va_list ap, size_t i)
{
	while (fmt[i] == '0' || fmt[i] == '-' || fmt[i] == ' ')
	{
		if (fmt[i] == '0' && flags->left == 0)
			flags->zero = 1;
		if (fmt[i] == '-')
		{
			flags->zero = 0;
			flags->left = 1;
		}
		i++;
	}
	if (parse_wildcard(&fmt[i], flags, ap))
		i++;
	else
	{
		if (flags->left)
			flags->left = ft_printf_atoi(&fmt[i]);
		else if (flags->zero)
			flags->zero = ft_printf_atoi(&fmt[i]);
		else if (!flags->zero && !flags->left)
			flags->width = ft_printf_atoi(&fmt[i]);
		while (fmt[i] && is_in_charset(fmt[i], "0123456789"))
			i++;
	}
	return (i);
}

static int	parse_precision(const char *fmt, t_flags *flags, va_list ap)
{
	size_t i;

	i = 0;
	if (fmt[i] == '.')
	{
		i++;
		flags->precision = -1;
		if (parse_wildcard(&fmt[i], flags, ap))
			i++;
		else
		{
			flags->precision = ft_printf_atoi(&fmt[i]);
			while (fmt[i] && is_in_charset(fmt[i], "0123456789"))
				i++;
		}
		if (flags->precision == 0)
			flags->precision = -1;
	}
	return (i);
}

static void	process_flags(t_flags *flags)
{
	if (flags->width < 0)
	{
		flags->left = -(flags->width);
		flags->width = 0;
	}
	if (flags->left < 0)
		flags->left = -(flags->left);
	if (flags->zero < 0)
	{
		flags->left = -(flags->zero);
		flags->zero = 0;
	}
}

int			is_valid_flag(const char *fmt, t_flags *flags, va_list ap)
{
	size_t	i;

	i = 1;
	ft_init_flags(flags);
	i += parse_flags(&fmt[i], flags, ap, 0);
	i += parse_precision(&fmt[i], flags, ap);
	if (is_in_charset(fmt[i], "scduipxX%"))
	{
		process_flags(flags);
		flags->id = fmt[i];
		return (i);
	}
	return (0);
}
