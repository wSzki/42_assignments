/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 03:29:26 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 03:29:33 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_free_split(char ***s)
{
	char	**split_line;

	split_line = *s;
	if (split_line)
	{
		while (*split_line)
		{
			free(*split_line);
			split_line++;
		}
		free(*split_line);
		free(*s);
		*s = NULL;
	}
}
