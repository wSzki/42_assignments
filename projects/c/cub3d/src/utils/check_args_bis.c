/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:02:58 by adlancel          #+#    #+#             */
/*   Updated: 2022/04/28 17:29:59 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_correct_map(t_global *g)
{
	int	i;
	int	j;

	i = 0;
	if (!g->m.map)
		cub_error(g, ERR_PARSING_MAP);
	while (g->m.map[i])
	{
		j = 0;
		while (g->m.map[i][j++])
		{
			if (ft_is_in_c(g->m.map[i][j], "NSWE"))
				g->m.player++;
			if (ft_is_in_c(g->m.map[i][j], "0WESN"))
				if (check_borders(g, i, j))
					cub_error(g, ERR_PARSING_MAP);
			if (j > g->m.cols)
				g->m.cols = j;
		}
		i++;
	}
	g->m.rows = i;
	if (g->m.player != 1)
		cub_error(g, ERR_PARSING_MAP);
	return (0);
}

static void	get_map_line(const char *line, t_global *g)
{
	int	i;

	i = 0;
	while (g->m.map[i] != NULL)
		i++;
	g->m.map[i] = ft_strdup(line);
	g->m.in_map += 1;
}

int	check_borders(t_global *g, int y, int x)
{
	if (y == 0 || x == 0)
		return (1);
	if (!g->m.map[y][x + 1] || !g->m.map[y + 1] || !g->m.map[y - 1])
		return (1);
	if (!g->m.map[y][x - 1])
		return (1);
	return (0);
}

void	get_line(char *line, t_global *g)
{
	if (is_map_line(line))
		get_map_line(line, g);
	else if (g->m.in_map == 0)
		get_path_or_value(line, g);
	else
		cub_error(g, ERR_PARSING_MAP);
}
