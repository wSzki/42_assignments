/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:40:03 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/01 18:40:24 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(char *op)
{
	if (ft_strcmp(">", op) == 0)
		return (YES);
	if (ft_strcmp("<", op) == 0)
		return (YES);
	if (ft_strcmp(">>", op) == 0)
		return (YES);
	if (ft_strcmp("<<", op) == 0)
		return (YES);
	return (NO);
}
