/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_fill_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:43:47 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/02 18:20:58 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_parsing_fill_path(t_global *g, char **container, int *checks)
{
	int	fd;

	if (*container != NULL)
		cub_error_str(g, MERR_PARAM_ALREADY_SET);
	fd = open(g->split[1], O_DIRECTORY | O_RDONLY);
	if (fd > -1)
	{
		close(fd);
		cub_error_str(g, MERR_PATH_TEXTURE);
	}
	fd = (open(g->split[1], O_RDONLY));
	if (fd < 0)
		cub_error_str(g, MERR_PATH_TEXTURE);
	close(fd);
	*container = ft_strdup(g->split[1]);
	*checks -= 1;
}
