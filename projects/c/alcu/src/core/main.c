/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 21:30:58 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/13 23:20:46 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "board.h"
#include "utils.h"
#include "display.h"

static int	final_value_to_aim(void)
{
	t_heap	*heap;
	int		final_value;

	heap = get_board()->first;
	final_value = 1;
	while (heap != get_board()->last)
	{
		heap = heap->next;
		final_value = (heap->nb_al % 4 != final_value);
	}
	return (final_value);
}

static int	get_ai_move(void)
{
	int			final_value;
	int			move;

	final_value = final_value_to_aim();
	move = (get_board()->last->nb_al - final_value) % 4;
	if (!move)
		move = 1;
	return (move);
}

static int	get_player_move(void)
{
	char	*line;
	int		move;

	line = NULL;
	while (!line)
	{
		if (get_board()->last->nb_al >= 3)
			display_info("Please choose between 1 and 3 items :");
		else if (get_board()->last->nb_al == 2)
			display_info("Please choose between 1 and 2 items :");
		else
			display_info("You have no choice but to take the 1 last item :");
		line = get_next_line(0);
		if (!line || (*line != '1'
				&& (*line != '2' || get_board()->last->nb_al < 2)
				&& (*line != '3' || get_board()->last->nb_al < 3))
			|| (line[1] != '\n' && line[1] != '\0'))
		{
			display_error("Invalid choice");
			line = (free(line), NULL);
		}
	}
	move = (*line - '0');
	return (free(line), move);
}

static void	apply_move(int move)
{
	t_board	*board;
	t_heap	*to_free;

	board = get_board();
	board->last->nb_al -= move;
	if (!board->last->nb_al)
	{
		to_free = board->last;
		board->last = board->last->previous;
		board->nb_of_heaps--;
		if (board->nb_of_heaps)
			board->last->next = NULL;
		else
			board->first = NULL;
		free(to_free);
	}
}

int	main(int argc, char **argv)
{
	int	fd;
	int	ai_move;

	fd = 0;
	if (argc < 1 || argc > 2)
		return (write(2, "ERROR\n", 6), 1);
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	if (fd == -1 || parse_board(fd) || get_board()->nb_of_heaps == 0)
		return (write(2, "ERROR\n", 6), 1);
	init_display();
	while (1)
	{
		ai_move = get_ai_move();
		apply_move(ai_move);
		if (get_board()->nb_of_heaps == 0)
			return (display_winner(0), endgame(), 0);
		display_board();
		display_ai_move(ai_move);
		apply_move(get_player_move());
		if (get_board()->nb_of_heaps == 0)
			return (display_winner(1), endgame(), 0);
	}
	return (0);
}
