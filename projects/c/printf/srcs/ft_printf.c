/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 01:15:40 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/27 14:22:51 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_init_flags(t_flags *flags)
{
	flags->zero = 0;
	flags->width = 0;
	flags->left = 0;
	flags->precision = 0;
	flags->id = 0;
}

static void	print_argument(t_flags *flags, va_list ap)
{
	int id;

	id = flags->id;
	if (id == 's')
		ft_printf_string(va_arg(ap, char*), flags);
	if (id == 'c')
		ft_printf_char(va_arg(ap, int), flags);
	if (id == '%')
		ft_printf_char('%', flags);
	if (id == 'd' || id == 'i')
		ft_printf_number(va_arg(ap, int), flags);
	if (id == 'x' || id == 'X')
		ft_printf_number(va_arg(ap, unsigned int), flags);
	if (id == 'u')
		ft_printf_number((unsigned int)va_arg(ap, long), flags);
	if (id == 'p')
		ft_printf_number((long)va_arg(ap, long), flags);
}

static void	ft_sub_printf(const char *fmt, t_flags *flags, va_list ap)
{
	int		i;
	size_t	processed_characters;

	i = -1;
	while (fmt[++i])
	{
		processed_characters = 0;
		if (fmt[i] == '%' && fmt[i + 1])
		{
			processed_characters = is_valid_flag(&fmt[i], flags, ap);
			if (processed_characters)
			{
				print_argument(flags, ap);
				i += processed_characters;
			}
			else
				ft_putchar_inc(fmt[i], flags);
		}
		else
			ft_putchar_inc(fmt[i], flags);
	}
	return ;
}

int			ft_printf(const char *fmt, ...)
{
	int		i;
	va_list	ap;
	t_flags	*flags;

	flags = malloc(sizeof(t_flags));
	if (!flags)
		return (0);
	flags->written = 0;
	ft_init_flags(flags);
	va_start(ap, fmt);
	ft_sub_printf(fmt, flags, ap);
	i = flags->written;
	va_end(ap);
	free(flags);
	return (i);
}
