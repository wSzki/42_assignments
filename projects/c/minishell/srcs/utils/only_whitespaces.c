/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:48:37 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/20 16:09:35 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]) == NO)
			return (NO);
		i++;
	}
	return (YES);
}
