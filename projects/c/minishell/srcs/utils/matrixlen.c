/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:42:44 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/20 16:18:22 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	matrixlen(char ***matrix)
{
	int	len;

	len = 0;
	if (matrix)
		while (matrix[len])
			len++;
	return (len);
}
