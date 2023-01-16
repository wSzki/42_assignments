/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_check_after_map.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:36:09 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:36:19 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_parsing_check_after_map(t_global *g, int fd)
{
	while (get_next_line(fd, &g->line) > 0)
	{
		if (g->line[0] != '\0')
		{
			free(g->line);
			g->line = NULL;
			cub_error_str(g, MERR_TRAILING_MAP);
		}
		free(g->line);
		g->line = NULL;
	}
}
