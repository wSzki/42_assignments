/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:10:45 by jraffin           #+#    #+#             */
/*   Updated: 2022/02/13 22:28:40 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "display.h"
#include "board.h"
#include "utils.h"

static int	get_max_heapsize_after(t_heap *heap)
{
	int		max_heap_size;

	max_heap_size = 0;
	while (heap)
	{
		if (heap->nb_al > max_heap_size)
			max_heap_size = heap->nb_al;
		heap = heap->next;
	}
	return (max_heap_size);
}

static void	display_nb_al(int heap_size_zone_len, int nb_al)
{
	char	buf[15];
	int		indent;
	int		len;
	int		i;

	len = ft_intlen(nb_al);
	indent = heap_size_zone_len - len - 1;
	i = 0;
	while (i < indent)
		buf[i++] = ' ';
	ft_itoa(nb_al, buf + indent);
	buf[indent + len] = ')';
	write(1, "\e[0;36m", 7);
	write(1, buf, heap_size_zone_len);
	write(1, "\e[0m", 4);
}

static void	undisplayed_heaps_msg(int nb_of_undisplayed_heaps)
{
	char	number[12];

	ft_itoa(nb_of_undisplayed_heaps, number);
	write(1, "\e[0;90m", 7);
	write(1, "^---- ", 6);
	write(1, number, ft_intlen(nb_of_undisplayed_heaps));
	write(1, " remaining undisplayed heaps. ----^", 35);
	write(1, "\e[0m\n", 5);
}

static void	display_heap(t_heap *heap, int max_width)
{
	int	max_heap_displayed_size;
	int	indent;
	int	i;

	if (max_width < 0)
		return ;
	max_heap_displayed_size = max_width / 2;
	indent = max_width % 2;
	if (heap->nb_al <= max_heap_displayed_size)
		indent += max_heap_displayed_size - heap->nb_al;
	else if (max_heap_displayed_size > 3)
		max_heap_displayed_size -= 3;
	else
		max_heap_displayed_size = 0;
	while (indent--)
		write(1, " ", 1);
	i = heap->nb_al;
	if (heap->nb_al > max_heap_displayed_size)
		i = max_heap_displayed_size;
	while (i--)
		write(1, " |", 2);
	if (heap->nb_al > max_heap_displayed_size)
		write(1, " (...)", 6);
	write(1, "\n", 1);
}

void	display_board(void)
{
	t_heap	*heap;
	int		max_heap_width;
	int		heap_size_zone_len;
	int		heaps_to_display;

	write(1, "\x1B[2J\x1B[H", 7);
	heaps_to_display = get_board()->nb_of_heaps;
	if (heaps_to_display > board_max_displayable_height())
	{
		heaps_to_display = board_max_displayable_height() - 1;
		undisplayed_heaps_msg(get_board()->nb_of_heaps - heaps_to_display);
	}
	heap = NULL;
	if (heaps_to_display)
		heap = get_board()->last;
	while (heaps_to_display-- > 1)
		heap = heap->previous;
	heap_size_zone_len = ft_intlen(get_max_heapsize_after(heap)) + 2;
	max_heap_width = max_displayable_width() - heap_size_zone_len;
	while (heap)
	{
		display_nb_al(heap_size_zone_len, heap->nb_al);
		display_heap(heap, max_heap_width);
		heap = heap->next;
	}
}
