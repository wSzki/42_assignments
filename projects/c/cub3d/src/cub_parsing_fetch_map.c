/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_fetch_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:37:10 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:37:35 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_parsing_fetch_map_line(t_global *g)
{
	int		i;
	char	**map_buffer;

	if (g->line == NULL)
		cub_error_str(g, MERR_PARAM_NOT_ENOUGH);
	if (cub_parsing_is_in_charset(g->line, " 01NSEW") == FALSE)
		cub_error_str(g, MERR_MAP_INVALID_CHAR);
	map_buffer = malloc(sizeof(char *) * \
			(cub_parsing_get_array_len(g->m.map) + 2));
	if (map_buffer == NULL)
		cub_error_str(g, MERR_SYS);
	map_buffer[cub_parsing_get_array_len(g->m.map) + 1] = NULL;
	i = 0;
	if (g->m.map)
	{
		while (g->m.map[i])
		{
			map_buffer[i] = ft_strdup(g->m.map[i]);
			free(g->m.map[i]);
			i++;
		}
	}
	free(g->m.map);
	map_buffer[i] = ft_strdup(g->line);
	g->m.map = map_buffer;
}

void	cub_parsing_fetch_map(t_global *g, int fd)
{
	cub_parsing_fetch_map_line(g);
	free(g->line);
	g->line = NULL;
	while (get_next_line(fd, &g->line) > 0)
	{
		if (g->line[0] == '\0')
		{
			free(g->line);
			g->line = NULL;
			break ;
		}
		cub_parsing_fetch_map_line(g);
		free(g->line);
		g->line = NULL;
	}
	free(g->line);
	g->line = NULL;
}
