/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:37:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/25 13:25:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

/*
**	---------------------------------INCLUDES---------------------------------#
*/

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <signal.h>

/*
**	---------------------------------ENUMS----------------------------------#
*/

enum	e_groups
{
	BLOCK,
	VERTICAL,
	HORIZONTAL
};

enum	e_colors
{
	WHITE,
	GREY,
	BLUE,
};

/*
**	---------------------------------STRUCTS----------------------------------#
*/

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
	int				color;
}				t_square;

/*
**	--------------------------------PROTOTYPES--------------------------------#
*/

int		is_in_block(t_coord pos, t_coord tocheck);
int		is_in_horizontal(t_coord pos, t_coord tocheck);
int		is_in_vertical(t_coord pos, t_coord tocheck);

void	board_print(t_square *board);
int		error(char *errstr);
char	*strdups(char *str, char *set);

void	debug(t_square *square, size_t i);
void	print_potential(unsigned short *masks, size_t size);

void	board_solver(t_square *board);
void	crossreference(t_square *board, t_square *square);

void	analyze_block(t_square *board, unsigned short *masks);

size_t	check_block(size_t groupindex, t_square *board,
		unsigned short mask, int *array);
size_t	check_horizontal(size_t groupindex, t_square *board,
		unsigned short mask, int *array);
size_t	check_vertical(size_t groupindex, t_square *board,
		unsigned short mask, int *array);

t_coord	index_to_coord(size_t group_index, char grouptype);
size_t	coord_to_index(t_coord coord, char grouptype);

char	*input_processing(int argc, char **argv);

#endif
