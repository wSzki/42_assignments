/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_fill_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:41:38 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:42:04 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_parsing_check_range(t_global *g, char *str)
{
	int	rgb;

	rgb = ft_atoi(str);
	if (!(rgb >= 0 && rgb < 256))
		cub_error_str(g, MERR_PARSING_RGB);
}

static unsigned int	cub_rgb_to_hex(t_global *g, unsigned int *c, char *rgb)
{
	int				i;
	char			**split;
	unsigned int	ret;
	unsigned int	t;

	t = 0;
	split = ft_split(rgb, ',');
	if (\
			cub_parsing_is_in_charset(rgb, "0123456789,") == FALSE || \
			cub_parsing_get_array_len(split) != 3 || \
			(int)*(c) != -1 \
		)
	{
		cub_parsing_free_split(&split, NULL);
		cub_error_str(g, MERR_PARSING_RGB);
	}
	i = -1;
	while (++i < 3)
		cub_parsing_check_range(g, split[i]);
	ret = (t << 24 | \
			ft_atoi(split[0]) << 16 | \
			ft_atoi(split[1]) << 8 | \
			ft_atoi(split[2]));
	cub_parsing_free_split(&split, NULL);
	return (ret);
}

void	cub_parsing_fill_color(t_global *g, unsigned int *c, int *checks)
{
	if ((int)*c != -1)
		cub_error_str(g, MERR_PARAM_ALREADY_SET);
	*c = cub_rgb_to_hex(g, c, g->split[1]);
	*checks -= 1;
}
