/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 00:26:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 14:29:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <signal.h>

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

typedef struct	s_coord
{
	int		x;
	int		y;
}				t_coord;

typedef struct	s_square
{
	unsigned short	potential;
	int				value;
	t_coord			pos;
}				t_square;

void	debug(t_square *square, size_t i)
{
	printf("BOARD[%ld]\n", i);
	printf("POS: %d,%d\n", square->pos.x, square->pos.y);
	printf("POTENTIAL:\n%d\n", square->potential);
	printf("VALUE: %d\n", square->value);
}

int		error(char *errstr)
{
	write(1, errstr, strlen(errstr));
	return (1);
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

void	init_board(t_square *board, char *start)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		board[i].pos = (t_coord){i % 9, i / 9};
		board[i].value = start[i] - '0';
		if (board[i].value == 0)
			board[i].potential = 0b111111111; //1111 1111 1
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

int		is_in_block(t_coord pos, t_coord tocheck)
{
	if (pos.x / 3 == tocheck.x / 3 && pos.y / 3 == tocheck.y / 3)
		return (1);
	return (0);
}

int		is_in_horizontal(t_coord pos, t_coord tocheck)
{
	if (pos.y == tocheck.y)
		return (1);
	return (0);
}

int		is_in_vertical(t_coord pos, t_coord tocheck)
{
	if (pos.x == tocheck.x)
		return (1);
	return (0);
}

unsigned short	*distill_potential(unsigned short potential, size_t *size)
{
	unsigned short	*masks;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (i < 9)
	{
		if ((potential & g_masks[i]) == g_masks[i])
			j++;
		i++;
	}
	masks = malloc(sizeof(unsigned short) * j);
	*size = j;
	i = 0;
	j = 0;
	while (i < 9)
	{
		if ((potential & g_masks[i]) == g_masks[i])
		{
			masks[j] = g_masks[i];
			j++;
		}
		i++;
	}
	return (masks);
}

//example X5,Y4 = 9 * Y = 36 + X = 41
// ((4 / 3 = 1) * 3 = 3) * 9 = 27 (which is where we start)
// (((4 / 3 = 1) * 3 = 3) + 2 = 5) * 9 = 45 (which is where we end)
size_t	check_block(t_coord subject, t_square *board, unsigned short mask)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = ((subject.y / 3) * 3) * 9;
	i += ((subject.x / 3) * 3);
	while (i < (((subject.y / 3) * 3) + 3) * 9)
	{
		if ((subject.y * 3) + subject.x != i)
			count += ((board[i].potential & mask) == mask);
		if ((subject.y * 3) + subject.x != i + 1)
			count += ((board[i + 1].potential & mask) == mask);
		if ((subject.y * 3) + subject.x != i + 2)
			count += ((board[i + 2].potential & mask) == mask);
		i += 9;
	}
	return (count);
}

//example X2,Y4 = 9 * Y = 36 + X = 38
size_t	check_horizontal(t_coord subject, t_square *board, unsigned short mask)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = subject.y * 9;
	while (i < (subject.y * 9) + 9)
	{
		if ((subject.y * 9) + subject.x != i)
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
		if ((subject.y * 9) + subject.x != i)
			count += ((board[i].potential & mask) == mask);
		i += 9;
	}
	return (count);
}

void	onlyoption_optimized(t_square *board, t_square *to_check, unsigned short *masks, size_t size)
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

//this can be optimized, we know the exact X and Y of the squares we need to check
void	onlyoption(t_square *board, t_square *to_check, unsigned short *masks, size_t size)
{
	size_t	i;
	size_t	j;
	int		count[3];

	i = 0;
	j = 0;
	while (i < size) //loop over every potential
	{
		j = 0;
		bzero(count, sizeof(int) * 3);
		while (j < 81) //check every square
		{
			if (&board[j] != to_check) //dont check itself
			{
				if (is_in_block(board[j].pos, to_check->pos) && (board[j].potential & masks[i]) == masks[i]) //if potential can be found
					count[0]++;
				if (is_in_horizontal(board[j].pos, to_check->pos) && (board[j].potential & masks[i]) == masks[i])
					count[1]++;
				if (is_in_vertical(board[j].pos, to_check->pos) && (board[j].potential & masks[i]) == masks[i])
					count[2]++;
			}
			j++;
		}
		if (!count[0] || !count[1] || !count[2]) //if in either BLOCK | HORIZON | VERT no potential can be found, then the value of the square can be set
		{
			to_check->potential = masks[i];
			break ;
		}
		i++;
	}
}

void	update(t_square *board, t_square *square, int value) //remove the potential, set value if one potential left.
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

int	elimination_check(t_square subject, t_square square) //check if they collide
{
	int		check;

	if (subject.potential & g_masks[square.value] != g_masks[square.value]) //potential has already been removed??? this shouldnt work
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
		if (&board[i] != square) //if they're not the same adress
			update(board, &board[i], elimination_check(board[i], *square)); //updates the square to reflect the change.
		i++;
	}
}

int		solved(t_square *board)
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

void	solver(t_square *board)
{
	size_t		i;

	while (!solved(board))
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

int		main(void)
{
	t_square	board[81];
//	char		start[] = "000807000006050071050000400000100064000005013900026007071009000009010000068400000";
	char		start[] = "000000000000003085001020000000507000004000100090000000500000073002010000000040009";

	init_board(board, start);
	print_board(board);
	solver(board);
	print_board(board);
	return (0);
}
