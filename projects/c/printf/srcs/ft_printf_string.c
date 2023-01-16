/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:51:41 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/25 19:35:22 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static const char	*ft_catch_s_null(const char *s, t_flags *flags)
{
	if (!s)
	{
		if (!(flags->precision == -1))
			s = "(null)";
		else
			s = "";
	}
	return (s);
}

static int			ft_process_precision(const char *s, t_flags *flags)
{
	int len;

	len = ft_strlen(s);
	if ((flags->width || flags->left) && flags->precision == -1)
		len = 0;
	if (flags->precision > 0 && flags->precision < len)
		len = flags->precision;
	return (len);
}

void				ft_printf_string(const char *s, t_flags *flags)
{
	int i;
	int fill;
	int len;

	i = 0;
	fill = 0;
	s = ft_catch_s_null(s, flags);
	len = ft_process_precision(s, flags);
	if (flags->width || flags->left || flags->zero)
		fill = flags->width + flags->left + flags->zero - len;
	if (fill)
	{
		if (flags->zero)
			ft_fill_zero_space(fill, '0', flags);
		else if (flags->width)
			ft_fill_zero_space(fill, ' ', flags);
	}
	if (flags->precision != -1)
		while (s[i] && i < len)
			ft_putchar_inc(s[i++], flags);
	if (flags->left)
		ft_fill_zero_space(fill, ' ', flags);
	return ;
}
