/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:35:38 by wszurkow          #+#    #+#             */
/*   Updated: 2021/01/24 23:25:18 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_flags
{
	int zero;
	int width;
	int left;
	int precision;
	int id;
	int written;

}				t_flags;

int				ft_printf(const char *fmt, ...);
void			ft_init_flags(t_flags *flags);

int				is_in_charset(char c, char *charset);
int				ft_count_digits(long n, t_flags *flags);
void			ft_fill_zero_space(int flag, int c, t_flags *flags);
size_t			ft_strlen(const char *str);
int				ft_printf_atoi(const char *str);

void			ft_putchar_inc(int c, t_flags *flags);
void			ft_putnbr_base_inc(long nbr, t_flags *flags);

int				is_valid_flag(const char *fmt, t_flags *flags, va_list ap);

void			ft_printf_char(const char c, t_flags *flags);
void			ft_printf_string(const char *s, t_flags *flags);
void			ft_printf_number(long n, t_flags *flags);

#endif
