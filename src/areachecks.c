/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   areachecks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:41:14 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/25 02:10:52 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

size_t	check_block(t_coord subject, t_square *board, unsigned short mask)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = ((subject.y / 3) * 3) * 9;
	i += ((subject.x / 3) * 3);
	while ((int)i < (((subject.y / 3) * 3) + 3) * 9)
	{
		if ((subject.y * 3) + subject.x != (int)i)
			count += ((board[i].potential & mask) == mask);
		if ((subject.y * 3) + subject.x != (int)i + 1)
			count += ((board[i + 1].potential & mask) == mask);
		if ((subject.y * 3) + subject.x != (int)i + 2)
			count += ((board[i + 2].potential & mask) == mask);
		i += 9;
	}
	return (count);
}

size_t	check_horizontal(t_coord subject, t_square *board, unsigned short mask)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = subject.y * 9;
	while ((int)i < (subject.y * 9) + 9)
	{
		if ((subject.y * 9) + subject.x != (int)i)
			count += ((board[i].potential & mask) == mask);
		i++;
	}
	return (count);
}

size_t	check_vertical(t_coord subject, t_square *board, unsigned short mask)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = subject.x;
	while (i < 81)
	{
		if ((subject.y * 9) + subject.x != (int)i)
			count += ((board[i].potential & mask) == mask);
		i += 9;
	}
	return (count);
}
