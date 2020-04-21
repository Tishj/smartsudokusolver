/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 00:26:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 15:37:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

unsigned short	g_masks[9] = {
	[0] = (1 << 0),
	[1] = (1 << 1),
	[2] = (1 << 2),
	[3] = (1 << 3),
	[4] = (1 << 4),
	[5] = (1 << 5),
	[6] = (1 << 6),
	[7] = (1 << 7),
	[8] = (1 << 8),
};

void	init_board(t_square *board, char *start)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		board[i].pos = (t_coord){i % 9, i / 9};
		board[i].value = start[i] - '0';
		if (board[i].value == 0)
			board[i].potential = 0b111111111;
		else
			board[i].potential = g_masks[board[i].value - 1];
		i++;
	}
}

int		setvalue(unsigned short potential)
{
	size_t	i;

	i = 0;
	while (i < 9)
	{
		if (potential == g_masks[i])
			return (i + 1);
		i++;
	}
	return (0);
}

unsigned short	*distill_potential(unsigned short potential, size_t *size)
{
	unsigned short	*masks;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	masks = malloc(sizeof(unsigned short) * 9);
	while (i < 9)
	{
		if ((potential & g_masks[i]) == g_masks[i])
		{
			masks[j] = g_masks[i];
			j++;
		}
		i++;
	}
	*size = j;
	return (masks);
}

void	onlyoption_optimized(t_square *board, t_square *to_check,
		unsigned short *masks, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (check_vertical(to_check->pos, board, masks[i]) == 0 ||
			check_block(to_check->pos, board, masks[i]) == 0 ||
			check_horizontal(to_check->pos, board, masks[i] == 0))
			break ;
		i++;
	}
	if (i != size)
		to_check->potential = masks[i];
}

void	onlyoption(t_square *board, t_square *to_check,
		unsigned short *masks, size_t size)
{
	size_t	i;
	size_t	j;
	int		count[3];

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		bzero(count, sizeof(int) * 3);
		while (j < 81)
		{
			if (&board[j] != to_check)
			{
				if (is_in_block(board[j].pos, to_check->pos) &&
					(board[j].potential & masks[i]) == masks[i])
					count[0]++;
				if (is_in_horizontal(board[j].pos, to_check->pos) &&
					(board[j].potential & masks[i]) == masks[i])
					count[1]++;
				if (is_in_vertical(board[j].pos, to_check->pos) &&
					(board[j].potential & masks[i]) == masks[i])
					count[2]++;
			}
			j++;
		}
		if (!count[0] || !count[1] || !count[2])
		{
			to_check->potential = masks[i];
			break ;
		}
		i++;
	}
}

void	square_update(t_square *board, t_square *square, int value)
{
	unsigned short	*masks;
	size_t			size;

	if (value)
		square->potential &= ~g_masks[value - 1];
	masks = distill_potential(square->potential, &size);
	onlyoption(board, square, masks, size);
//	onlyoption_optimized(board, square, masks, size);
	square->value = setvalue(square->potential);
	free(masks);
}

int	elimination_check(t_square subject, t_square square)
{
	int		check;

	if ((subject.potential & g_masks[square.value - 1])
		!= g_masks[square.value - 1])
		return (0);
	check = (is_in_block(subject.pos, square.pos) ||
			is_in_horizontal(subject.pos, square.pos) ||
			is_in_vertical(subject.pos, square.pos));
	return (check) ? square.value : 0;
}

void	crossreference(t_square *board, t_square *square)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		if (&board[i] != square)
			square_update(board, &board[i],
			elimination_check(board[i], *square));
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_square	board[81];
	char		*start;

	start = input_processing(argc, argv);
	init_board(board, start);
	board_solver(board);
	print_board(board);
	return (0);
}
