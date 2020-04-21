/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:39:39 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 14:40:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void	print_board(t_square *board)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		printf("%c %c %c %c %c %c %c %c %c\n",
		board[i].value + '0', board[i + 1].value + '0',
		board[i + 2].value + '0', board[i + 3].value + '0',
		board[i + 4].value + '0', board[i + 5].value + '0',
		board[i + 6].value + '0', board[i + 7].value + '0',
		board[i + 8].value + '0');
		i += 9;
	}
	write(1, "\n", 1);
}

int		error(char *errstr)
{
	write(1, errstr, strlen(errstr));
	return (1);
}
