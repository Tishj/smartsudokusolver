/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 15:15:10 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 15:34:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

char	*input_string(int fd)
{
	char	raw[200];

	(void)read(fd, raw, 199);
	return (strdups(raw, "0123456789"));
}

char	*input_processing(int argc, char **argv)
{
	int		fd;
	char	*input;

	if (argc != 2 || (!argv || !argv[1]))
		exit(error("Please provide (only) one file\n"));
	fd = open(argv[1], O_RDONLY);
	if (read(fd, (void *)0, 0) == -1)
		exit(error("Please provide a valid file\n"));
	input = input_string(fd);
	return (input);
}
