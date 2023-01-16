/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:40:00 by adlancel          #+#    #+#             */
/*   Updated: 2022/05/02 18:24:52 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cub_parsing_open_map_file(t_global *g, char *path, int *fd)
{
	int	len;

	len = (ft_strlen(path));
	if (len < 5)
		cub_error_str(g, MERR_MAP_EXTENSION);
	len--;
	if (path[len - 3] != '.')
		cub_error_str(g, MERR_MAP_EXTENSION);
	if (ft_strncmp(&path[len - 2], "cub", 3) != 0)
		cub_error_str(g, MERR_MAP_EXTENSION);
	*fd = open(path, O_DIRECTORY | O_RDONLY);
	if (*fd > -1)
		cub_error_str(g, MERR_CANNOT_OPEN_MAP);
	*fd = open(path, O_RDONLY);
	g->fd = *fd;
	if (*fd < 0)
		cub_error_str(g, MERR_CANNOT_OPEN_MAP);
}

static void	cub_parsing(t_global *g, char *path)
{
	int		fd;
	int		checks;

	checks = 6;
	cub_parsing_open_map_file(g, path, &fd);
	cub_parsing_fetch_data(g, fd, &checks);
	cub_parsing_skip_newlines(g, fd, checks);
	cub_parsing_fetch_map(g, fd);
	cub_parsing_check_after_map(g, fd);
	cub_parsing_validate_map(g);
	close(fd);
	g->fd = -1;
}

int	main(int ac, char **av)
{
	t_global	*g;
	char		*arg_err;

	arg_err = "Only one argument (.cub path) is accepted\n";
	if (ac != 2)
	{
		if (write(2, "Error\n", 6) < 0)
			cub_error(g, errno);
		if (write(2, arg_err, ft_strlen(arg_err)) < 0)
			cub_error(g, errno);
		exit(1);
	}
	g = malloc(sizeof(t_global));
	if (g == NULL)
		cub_error_str(g, MERR_SYS);
	g->x.mlx = NULL;
	cub_init(&g);
	cub_parsing(g, av[1]);
	cub_init_mlx(&g);
	cub_init_xpm(&g);
	cub_display(g);
	cub_free_all(g);
	return (0);
}
