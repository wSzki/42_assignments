/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 22:38:31 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/23 23:19:58 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_printf_char(const char c, t_flags *flags)
{
	if (flags->left)
	{
		flags->left--;
		ft_putchar_inc(c, flags);
		ft_fill_zero_space(flags->left, ' ', flags);
	}
	else if (flags->width)
	{
		flags->width--;
		ft_fill_zero_space(flags->width, ' ', flags);
		ft_putchar_inc(c, flags);
	}
	else if (flags->zero && flags->id == '%')
	{
		flags->zero--;
		ft_fill_zero_space(flags->zero, '0', flags);
		ft_putchar_inc('%', flags);
	}
	else
		ft_putchar_inc(c, flags);
	return ;
}
