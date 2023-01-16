/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_validate_map.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:28:01 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:34:24 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_parsing_check_map_edges(t_global *g)
{
	int		i;
	int		j;
	int		len;
	char	**m;

	m = g->m.map;
	if (cub_parsing_is_in_charset(m[0], " 1") == FALSE)
		cub_error_str(g, MERR_MAP_NOT_CLOSED);
	if (cub_parsing_is_in_charset(m[g->m.rows - 1], " 1") == FALSE)
		cub_error_str(g, MERR_MAP_NOT_CLOSED);
	i = -1;
	while (m[++i])
	{
		j = 0;
		while (cub_parsing_is_whitespace(m[i][j]))
			j++;
		if (m[i][j] != '1')
			cub_error_str(g, MERR_MAP_NOT_CLOSED);
		len = ft_strlen(m[i]) - 1;
		while (cub_parsing_is_whitespace(m[i][len]))
			len--;
		if (m[i][len] != '1')
			cub_error_str(g, MERR_MAP_NOT_CLOSED);
	}
}

static void	cub_parsing_check_map_inner(t_global *g)
{
	int		i;
	int		j;
	char	**m;

	i = 1;
	m = g->m.map;
	while (m[i + 1] != NULL)
	{
		j = 1;
		while (m[i][j + 1] != '\0')
		{
			if (cub_parsing_is_in(m[i][j], "0NSEW"))
				if (\
						cub_parsing_is_in(m[i - 1][j], "01NSEW") == FALSE || \
						cub_parsing_is_in(m[i + 1][j], "01NSEW") == FALSE || \
						cub_parsing_is_in(m[i][j - 1], "01NSEW") == FALSE || \
						cub_parsing_is_in(m[i][j + 1], "01NSEW") == FALSE \
					)
					cub_error_str(g, MERR_MAP_NOT_CLOSED);
			j++;
		}
		i++;
	}
}

static void	cub_parsing_check_unique_player(t_global *g)
{
	int		i;
	int		j;
	char	**m;
	int		pos_found;

	i = -1;
	j = -1;
	m = g->m.map;
	pos_found = FALSE;
	while (m[++i])
	{
		j = -1;
		while (m[i][++j])
		{
			if (cub_parsing_is_in(m[i][j], "NSEW"))
			{
				if (pos_found == TRUE)
					cub_error_str(g, MERR_MULT_PLAYER_POS);
				if (pos_found == FALSE)
					pos_found = TRUE;
			}
		}
	}
	if (pos_found == FALSE)
		cub_error_str(g, MERR_PLAYER_NOT_SET);
}

void	cub_parsing_validate_map(t_global *g)
{
	int		i;
	int		largest_line;
	char	**m;

	i = -1;
	m = g->m.map;
	largest_line = 0;
	while (m[++i])
	{
		if (ft_strlen(m[i]) > largest_line)
			largest_line = ft_strlen(m[i]);
	}
	g->m.rows = cub_parsing_get_array_len(m);
	g->m.cols = largest_line;
	if (g->m.rows < 3 || g->m.cols < 3)
		cub_error_str(g, MERR_MAP_TOO_SMALL);
	cub_parsing_check_map_edges(g);
	cub_parsing_check_map_inner(g);
	cub_parsing_check_unique_player(g);
}
