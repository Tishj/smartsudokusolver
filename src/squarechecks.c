/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   squarechecks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:41:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 14:41:34 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

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
