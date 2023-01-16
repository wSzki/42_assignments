/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 04:03:44 by jraffin           #+#    #+#             */
/*   Updated: 2022/02/13 23:21:32 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "board.h"
#include "utils.h"

t_board	*get_board(void)
{
	static t_board	board;

	return (&board);
}

static t_heap	*new_heap(int nb_al, t_heap *previous)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->nb_al = nb_al;
	heap->previous = previous;
	heap->next = NULL;
	return (heap);
}

static int	line_is_valid_number(const char *line, int *nbr)
{
	unsigned int	tmp;

	if (!*line || *line == '\n')
		return (0);
	tmp = 0;
	while (*line == '0')
		line++;
	while ('0' <= *line && *line <= '9')
	{
		tmp *= 10;
		tmp += *line - '0';
		if (tmp > 10000)
			return (0);
		line++;
	}
	if (tmp < 1 || (*line && *line != '\n'))
		return (0);
	*nbr = tmp;
	return (1);
}

int	parse_board(int fd)
{
	t_board	*board;
	char	*line;
	int		nbr;

	if (fd == -1)
		return (1);
	board = get_board();
	line = get_next_line(fd);
	while (line && line_is_valid_number(line, &nbr))
	{
		board->last = new_heap(nbr, board->last);
		if (!board->first)
			board->first = board->last;
		else
			board->last->previous->next = board->last;
		board->nb_of_heaps++;
		line = (free(line), get_next_line(fd));
	}
	close(fd);
	get_next_line(fd);
	fd = (close(fd), open("/dev/tty", O_RDONLY));
	if (!line || *line == '\n' || !*line || fd == -1)
		return (free(line), 0);
	free(line);
	return (1);
}
