/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   board.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:51:21 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 14:52:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

int		board_issolved(t_square *board)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		if (board[i].value == 0)
			return (0);
		i++;
	}
	return (1);
}

void	board_solver(t_square *board)
{
	size_t		i;

	while (!board_issolved(board))
	{
		i = 0;
		while (i < 81)
		{
			if (board[i].value)
				crossreference(board, &board[i]);
			i++;
		}
	}
}

