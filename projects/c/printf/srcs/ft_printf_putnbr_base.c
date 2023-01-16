/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 20:02:32 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/27 14:25:24 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_putnbr_base_inc(long nbr, t_flags *flags)
{
	char *base;

	if (nbr < 0)
		nbr = -nbr;
	if (flags->id == 'd' || flags->id == 'i' || flags->id == 'u')
		base = "0123456789";
	if (flags->id == 'x' || flags->id == 'p')
		base = "0123456789abcdef";
	if (flags->id == 'X')
		base = "0123456789ABCDEF";
	if (nbr >= (long)ft_strlen(base))
		ft_putnbr_base_inc(nbr / (long)ft_strlen(base), flags);
	nbr = base[nbr % (long)ft_strlen(base)];
	write(1, &nbr, 1);
	flags->written += 1;
}
