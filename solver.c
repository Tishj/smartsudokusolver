/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 00:26:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/20 01:32:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

enum	e_value
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
};

unsigned short	g_masks[9] = {
	[ONE] = '\x8000',
	[TWO] = '\x4000',
	[THREE] = '\x2000',
	[FOUR] = '\x1000',
	[FIVE] = '\x800',
	[SIX] = '\x400',
	[SEVEN] = '\x200',
	[EIGHT] = '\x100',
	[NINE] = '\x80',
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
	t_coord	pos;
}				t_square;

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
}

void	init_board(t_square *board)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		board[i].pos = (t_coord){i % 9, i / 9};
		board[i].potential = (unsigned short)'\xFF80';
		board[i].value = 0;
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

void	update(t_square *square, int value) //remove the potential, set value if one potential left.
{
	square->potential |= g_masks[value];
	square->value = setvalue(square->potential);
}

int	elimination_check(t_square subject, t_square square) //check if they collide
{
	if (subject.potential & g_masks[square.value] != g_masks[square.value]) //potential has already been removed
		return (0);
	if (subject.pos.x == square.pos.x || subject.pos.y == square.pos.y) //Horizontal and vertical check
		return (1);
	if (subject.pos.x / 3 == square.pos.x / 3 && subject.pos.y / 3 == square.pos.y / 3)
		return (1);
	//need to write a check to check if in the same box.
	return (0);
}

void	crossreference(t_square *board, t_square *square)
{
	size_t	i;

	i = 0;
	while (i < 81)
	{
		if (&board[i] != square)
			if (elimination_check(board[i], *square))
				update(&board[i], square->value);
		i++;
	}
}

int		solved(t_square *board)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < 81)
	{
		if (board->value != 0)
			len++;
		i++;
	}
	return (len == 81);
}

void	solver(t_square *board)
{
	size_t		i;

	i = 0;
	while (!solved(board))
	{
		while (i < 81 && !board[i].value)
			i++;
		if (i == 81)
			exit(1);//error
		crossreference(board, &board[i]);
	}
}

int		main(void)
{
	t_square	board[81];
	char		*start; //still need to add the starting squares somehow :/

	init_board(board);
	solver(board);
	return (0);
}
