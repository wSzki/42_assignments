/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_skip_newlines.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:38:35 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:38:43 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_parsing_skip_newlines(t_global *g, int fd, int checks)
{
	if (checks != 0)
		cub_error_str(g, MERR_PARAM_NOT_ENOUGH);
	while (get_next_line(fd, &g->line) > 0)
	{
		if (g->line[0] != '\0')
			break ;
		free(g->line);
		g->line = NULL;
	}
}
