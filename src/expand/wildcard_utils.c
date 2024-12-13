/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:15:08 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:15:09 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	entry_pattern_match(const char *entry, const char *pattern)
{
	while (*entry && *pattern)
	{
		if (*pattern == '*')
			return (match_suffix(entry, pattern + 1));
		if (*pattern != *entry)
			return (0);
		entry++;
		pattern++;
	}
	return ((*pattern == '\0' || *pattern == '*')
		&& *entry == '\0');
}

int	match_suffix(const char *entry, const char *pattern)
{
	if (*pattern == '\0')
		return (1);
	while (*entry)
	{
		if (entry_pattern_match(entry, pattern))
			return (1);
		entry++;
	}
	return (0);
}

int	include_hidden(char first, char *entry)
{
	if (first == '.' && entry[0] == '.')
		return (1);
	return (!(first != '.' && entry[0] == '.'));
}

ssize_t	entry_count(char *pattern)
{
	struct dirent	*entry;
	ssize_t			len;
	DIR				*cur_dir;

	cur_dir = opendir(".");
	if (!cur_dir)
		return (perror("Failed to open directory"), -1);
	entry = readdir(cur_dir);
	len = 0;
	while (entry)
	{
		if (entry_pattern_match(entry->d_name, pattern))
			if (include_hidden(pattern[0], entry->d_name))
				len++;
		entry = readdir(cur_dir);
	}
	closedir(cur_dir);
	return (len);
}

ssize_t	entries_count(char **args)
{
	ssize_t	len;
	ssize_t	i;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			len += entry_count(args[i]);
		i++;
	}
	return (len);
}
