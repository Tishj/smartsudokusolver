/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solver.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:37:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 15:31:48 by tbruinem      ########   odam.nl         */
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
}				t_square;

/*
**	--------------------------------PROTOTYPES--------------------------------#
*/

int		is_in_block(t_coord pos, t_coord tocheck);
int		is_in_horizontal(t_coord pos, t_coord tocheck);
int		is_in_vertical(t_coord pos, t_coord tocheck);

void	print_board(t_square *board);
int		error(char *errstr);
char	*strdups(char *str, char *set);

void	debug(t_square *square, size_t i);
void	print_potential(unsigned short *masks, size_t size);

void	board_solver(t_square *board);
void	crossreference(t_square *board, t_square *square);

size_t	check_block(t_coord subject, t_square *board, unsigned short mask);
size_t	check_horizontal(t_coord subject, t_square *board, unsigned short mask);
size_t	check_vertical(t_coord subject, t_square *board, unsigned short mask);

char	*input_processing(int argc, char **argv);

#endif
