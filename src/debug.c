/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:40:03 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 14:40:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void	debug(t_square *square, size_t i)
{
	printf("BOARD[%ld]\n", i);
	printf("POS: %d,%d\n", square->pos.x, square->pos.y);
	printf("POTENTIAL:\n%d\n", square->potential);
	printf("VALUE: %d\n", square->value);
}

void	print_potential(unsigned short *masks, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		printf("%d\n", masks[i]);
		i++;
	}
	printf("\n");
}
