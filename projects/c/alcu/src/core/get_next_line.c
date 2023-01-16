/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:42:49 by jraffin           #+#    #+#             */
/*   Updated: 2022/02/13 23:01:12 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"

static void	reset_list(t_gnlbuflist *list)
{
	t_gnlbuf	*to_free;
	int			errno_save;

	errno_save = errno;
	while (list->first)
	{
		to_free = list->first;
		list->first = list->first->next;
		free(to_free);
	}
	errno = errno_save;
	list->last = NULL;
	list->nb_buf = 0;
	list->cursor = 0;
	list->last_size = 0;
	list->found_nl = NULL;
}

static int	read_input(t_gnlbuflist *list, int fd)
{
	ssize_t		readval;

	while (!list->found_nl)
	{
		if (list->last_size == GNL_BUFSIZE || !list->nb_buf)
		{
			if (!list->nb_buf)
				list->last = (list->first = malloc(sizeof(t_gnlbuf)));
			else
				list->last = (list->last->next = malloc(sizeof(t_gnlbuf)));
			if (!list->last)
				return (1);
			list->last->next = NULL;
			list->last_size = 0;
			list->nb_buf++;
		}
		readval = read(fd, list->last->data + list->last_size,
				GNL_BUFSIZE - list->last_size);
		if (readval <= 0)
			return (readval < 0);
		list->found_nl = ft_memchr(
				list->last->data + list->last_size, '\n', readval);
		list->last_size += readval;
	}
	return (0);
}

static void	extract_to_line(t_gnlbuflist *list, char *line, size_t linelen)
{
	t_gnlbuf	*to_free;
	size_t		copylen;

	while (linelen)
	{
		copylen = GNL_BUFSIZE - list->cursor;
		if (linelen < copylen)
			copylen = linelen;
		ft_memcpy(line, list->first->data + list->cursor, copylen);
		list->cursor += copylen;
		if (list->cursor == GNL_BUFSIZE
			|| (list->nb_buf == 1 && list->cursor == list->last_size))
		{
			to_free = list->first;
			list->first = list->first->next;
			free(to_free);
			list->nb_buf--;
			list->cursor = 0;
		}
		if (!list->nb_buf)
			list->last = (list->last_size = 0, NULL);
		line += copylen;
		linelen -= copylen;
	}
}

static char	*retreive_line(t_gnlbuflist *list)
{
	char	*line;
	size_t	linelen;
	size_t	last_maxlen;

	if (list->found_nl)
		last_maxlen = (list->found_nl - list->last->data) + 1;
	else
		last_maxlen = list->last_size;
	linelen = (((list->nb_buf - 1) * GNL_BUFSIZE) - list->cursor) + last_maxlen;
	if (!linelen)
		return (reset_list(list), NULL);
	line = malloc(sizeof(char) * (linelen + 1));
	if (!line)
		return (reset_list(list), NULL);
	line[linelen] = '\0';
	extract_to_line(list, line, linelen);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnlbuflist	buflist[GNL_FD_MAXSIZE];
	char				*line;

	if (GNL_BUFSIZE == 0)
		return (errno = ENOMEM, NULL);
	if (fd < 0 || fd >= GNL_FD_MAXSIZE)
		return (errno = EBADFD, NULL);
	if (read(fd, NULL, 0)
		|| (!buflist[fd].found_nl && read_input(&buflist[fd], fd)))
		return (reset_list(&buflist[fd]), NULL);
	line = retreive_line(&buflist[fd]);
	if (buflist[fd].nb_buf)
		buflist[fd].found_nl = ft_memchr(
				buflist[fd].first->data + buflist[fd].cursor, '\n',
				buflist[fd].last_size - buflist[fd].cursor);
	else
		buflist[fd].found_nl = NULL;
	return (line);
}
