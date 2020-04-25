/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:39:39 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 16:31:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

//might be useful to print in colors to distinguish between starting numbers and discovered ones
void	board_print(t_square *board)
{
	size_t	i;
	char	*colors[] = {
		[WHITE]	= "\x1b[38;5;236m",
		[BLUE] = "\x1b[36;1m",
		[GREY] = "\x1b[4m",
	};

	i = 0;
	while (i < 81)
	{
		printf("%s%c%s ", colors[board[i].color], board[i].value + '0', "\x1b[0m");
//		printf("%c ", board[i].value + '0');
		i++;
		if (i % 9 == 0)
			printf("\n");
	}
	write(1, "\n", 1);
}

int		error(char *errstr)
{
	write(1, errstr, strlen(errstr));
	return (1);
}
