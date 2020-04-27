/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   areachecks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:41:14 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/26 00:39:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

size_t	coord_to_index(t_coord coord, char grouptype)
{
	if (grouptype == BLOCK)
		return (((coord.y / 3) * 3) + (coord.x / 3));
	if (grouptype == VERTICAL)
		return (coord.x);
	return (coord.y);
}

t_coord	index_to_coord(size_t group_index, char grouptype)
{
	if (grouptype == BLOCK)
		return ((t_coord){(group_index % 3) * 3, (group_index / 3) * 3});
	if (grouptype == VERTICAL)
		return ((t_coord){group_index, 0});
	return ((t_coord){0, group_index * 9});
}

void	print_group(int *sizes, int indices[9][9])
{
	size_t	pot;
	size_t	i;

	pot = 0;
	while (pot < 9)
	{
		i = 0;
		while ((int)i < sizes[pot])
		{
			printf("POTENTIAL OF %ld | %ld | %d\n", pot + 1, i, indices[pot][i]);
			i++;
		}
		pot++;
	}
//	if (i && pot)
//		sleep(1);
	printf("\n\n");
}

//loop over the entire block, check the potentials for everything inside the block
//
void	analyze_block(t_square *board, unsigned short *masks) //find pairs
{
	int			pt_index[9][9]; //[POTENTIAL][INDEX]
	int			sizes[9]; //indices per potential
	size_t		i; //potential index

	i = 0;
	while (i < 9)
	{
		sizes[i] = check_block(i, board, masks[i], pt_index[i]);
		i++;
	}
//	(void)sizes;
	print_group(sizes, pt_index);
	//check for similarities
	//both 35 and 46 can be only 5 and 7 for instance (only being the keyword)
}

size_t	check_block(size_t groupindex, t_square *board,
		unsigned short mask, int *array)
{
	size_t	i;
	size_t	j;
	size_t	count;
	t_coord	coord;

	count = 0;
	coord = index_to_coord(groupindex, BLOCK);
	i = ((coord.y / 3) * 3) * 9;
	i += ((coord.x / 3) * 3);
	while ((int)i < (((coord.y / 3) * 3) + 3) * 9)
	{
		j = 0;
		while (j < 3)
		{
			if (array)
				array[count] = ((board[i + j].potential & mask) == mask) ?
				i + j : 0;
			count += ((board[i + j].potential & mask) == mask);
			j++;
		}
		i += 9;
	}
	return (count);
}

size_t	check_horizontal(size_t groupindex, t_square *board,
		unsigned short mask, int *array)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = (groupindex * 9);
	while (i < (groupindex * 9) + 9)
	{
		if (array)
			array[count] = ((board[i].potential & mask) == mask) ?
			i : 0;
		count += ((board[i].potential & mask) == mask);
		i++;
	}
	return (count);
}

size_t	check_vertical(size_t groupindex, t_square *board,
		unsigned short mask, int *array)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = groupindex;
	while (i < 81)
	{
		if (array)
			array[count] = ((board[i].potential & mask) == mask) ?
			i : 0;
		count += ((board[i].potential & mask) == mask);
		i += 9;
	}
	return (count);
}
