/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 00:26:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/26 16:41:30 by tbruinem      ########   odam.nl         */
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

void	board_init(t_square *board, char *start)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		board[i].pos = (t_coord){i % 9, i / 9};
		board[i].value = start[i] - '0';
		if (board[i].value == 0)
		{
			board[i].potential = 0b111111111;
			board[i].color = WHITE;
		}
		else
		{
			board[i].potential = g_masks[board[i].value - 1];
			board[i].color = GREY;
		}
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
		if (check_vertical(coord_to_index(to_check->pos, VERTICAL),
			board, masks[i], NULL) == 1 ||
			check_block(coord_to_index(to_check->pos, BLOCK),
			board, masks[i], NULL) == 1 ||
			check_horizontal(coord_to_index(to_check->pos, HORIZONTAL),
			board, masks[i], NULL) == 1)
		{
			break ;
		}
//		sleep(10);
		i++;
	}
	if (i < size)
		to_check->potential = masks[i];
}

//need to add support for the possibility where two values can only be inside 2 places,
//then their potential needs to be updated to be limited to those two values, nothing else
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
				{
					count[0]++;
					printf("BLOCK: %ld | count: %d\n", j, count[0]);
				}
				if (is_in_horizontal(board[j].pos, to_check->pos) &&
					(board[j].potential & masks[i]) == masks[i])
				{
					count[1]++;
					printf("HORIZ: %ld | count: %d\n", j, count[1]);
				}
				if (is_in_vertical(board[j].pos, to_check->pos) &&
					(board[j].potential & masks[i]) == masks[i])
				{
					count[2]++;
					printf("VERT: %ld | count: %d\n", j, count[2]);
				}
			}
			j++;
		}
		if (!count[0] || !count[1] || !count[2])
		{
			to_check->potential = masks[i];
			break ;
		}
//		sleep(10);
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
//	onlyoption(board, square, masks, size);
	onlyoption_optimized(board, square, masks, size);
	square->value = setvalue(square->potential);
	if (square->value)
	{
		square->color = BLUE;
		board_print(board);
		sleep(1);
	}
	free(masks);
//	analyze_block(board, g_masks);
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
		if (&board[i] != square && board[i].value == 0)
			square_update(board, &board[i],
			elimination_check(board[i], *square));
		i++;
	}
}

void	pot_print(unsigned short pot, unsigned short *masks, size_t i)
{
	printf("INDEX: %-2ld : [%c][%c][%c][%c][%c][%c][%c][%c][%c]\n", i,
		((pot & masks[0]) == masks[0]) ? '1' : ' ',
		((pot & masks[1]) == masks[1]) ? '2' : ' ',
		((pot & masks[2]) == masks[2]) ? '3' : ' ',
		((pot & masks[3]) == masks[3]) ? '4' : ' ',
		((pot & masks[4]) == masks[4]) ? '5' : ' ',
		((pot & masks[5]) == masks[5]) ? '6' : ' ',
		((pot & masks[6]) == masks[6]) ? '7' : ' ',
		((pot & masks[7]) == masks[7]) ? '8' : ' ',
		((pot & masks[8]) == masks[8]) ? '9' : ' ');
}

void	tmp_debug(t_square *board, unsigned short *masks)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		pot_print(board[i].potential, masks, i);
		i++;
	}
	sleep(1);
}

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
		tmp_debug(board, g_masks);
	}
}

int		main(int argc, char **argv)
{
	t_square	board[81];
	char		*start;

	start = input_processing(argc, argv);
	board_init(board, start);
	board_print(board);
	board_solver(board);
	board_print(board);
	return (0);
}
