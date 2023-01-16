/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:35:42 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/02 18:29:36 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>
#include <string.h>

void	cub_error(t_global *g, int error)
{
	(void) error;
	cub_free_all(g);
	exit (errno);
}

void	cub_error_str(t_global *g, char *error)
{
	if (write(2, "Error\n", 6) < 0)
		cub_error(g, errno);
	if (write(2, error, ft_strlen(error)) < 0)
		cub_error(g, errno);
	cub_free_all(g);
	exit (errno);
}
