/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:37:38 by wszurkow          #+#    #+#             */
/*   Updated: 2022/02/13 23:24:49 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "board.h"
#include "utils.h"
#include "display.h"

#define ALCU_DISPLAY_MAX_WIDTH 80
#define ALCU_DISPLAY_MAX_BOARD_HEIGHT 20

void	init_display(void)
{
	display_board();
	display_welcome();
}

int	max_displayable_width(void)
{
	return (ALCU_DISPLAY_MAX_WIDTH);
}

int	board_max_displayable_height(void)
{
	return (ALCU_DISPLAY_MAX_BOARD_HEIGHT);
}

void	endgame(void)
{
	write(1, "\e[1;33m", 7);
	write(1, "PRESS ENTER TO EXIT...", 22);
	write(1, "\e[0m\n", 5);
	free(get_next_line(0));
	write(1, "\x1B[2J\x1B[H", 7);
}
