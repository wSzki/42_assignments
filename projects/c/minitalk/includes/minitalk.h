/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 19:19:35 by wszurkow          #+#    #+#             */
/*   Updated: 2021/08/19 17:21:19 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
void	mt_putnbr(int n);
void	mt_putstr(char *str);
int		mt_atoi(const char *str);
void	mt_print_exit(char *str);
void	mt_print_pid(int ac);
#endif
