/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:42:34 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:45:22 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	restore_io(int *i, int *fd, int *fd_in, int *original_io)
{
	*i += 1;
	close(fd[1]);
	*fd_in = fd[0];
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
}

int	restore_io_error(int *original_io)
{
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	return (ERROR);
}

int	restore_io_continue(int *original_io, int *i)
{
	*i += 1;
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	return (CONTINUE);
}
