/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testbits.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 18:35:12 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/20 18:39:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		main(void)
{
	unsigned short	pot;
	unsigned short	mask;

	mask = 128;
	pot = 383;
	printf("return value: of %d & %d = %d\n", pot, mask, pot & mask);
	return (0);
}
