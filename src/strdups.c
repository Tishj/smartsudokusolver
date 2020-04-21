/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strdups.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 15:27:02 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/21 15:34:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

size_t	strlens(char *str, char *set)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (strchr(set, str[i]) != NULL)
			len++;
		i++;
	}
	return (len);
}

char	*strdups(char *str, char *set)
{
	size_t	len;
	size_t	i;
	size_t	n;
	char	*new;

	i = 0;
	n = 0;
	len = strlens(str, set);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (n < len)
	{
		if (strchr(set, str[i]) != NULL)
		{
			new[n] = str[i];
			n++;
		}
		i++;
	}
	new[n] = 0;
	return (new);
}
