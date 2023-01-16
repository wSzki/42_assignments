/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 02:45:38 by jraffin           #+#    #+#             */
/*   Updated: 2022/02/13 20:55:09 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/select.h>
# include "board.h"

# ifndef GNL_BUFSIZE
#  define GNL_BUFSIZE 4096
# endif

# ifndef GNL_FD_MAXSIZE
#  define GNL_FD_MAXSIZE FD_SETSIZE
# endif

typedef struct s_gnlbuf
{
	char			data[GNL_BUFSIZE];
	struct s_gnlbuf	*next;
}	t_gnlbuf;

typedef struct s_gnlbuflst
{
	t_gnlbuf		*first;
	t_gnlbuf		*last;
	size_t			nb_buf;
	size_t			cursor;
	size_t			last_size;
	char			*found_nl;
}	t_gnlbuflist;

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_itoa(int value, char *str);
size_t	ft_strlen(const char *s);
int		ft_intlen(int n);

char	*get_next_line(int fd);

#endif
