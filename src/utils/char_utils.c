/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:40:06 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/03 21:40:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_char(char *str, char h)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == h)
			count++;
		i++;
	}
	return (count);
}

size_t	first_occur(char *str, char h)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == h)
			return (i);
		i++;
	}
	return (0);
}

int	count_dots(char **dirs)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (dirs[i])
	{
		if (!ft_strcmp(dirs[i], ".."))
			count++;
		i++;
	}
	return (count);
}

int	is_tilde(char *s1, char *s2)
{
	if (!ft_strcmp(s1, "~") && !s2)
		return (1);
	return (0);
}

int	is_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
