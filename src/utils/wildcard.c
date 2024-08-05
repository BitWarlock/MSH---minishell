/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:15:12 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/05 04:45:11 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_arg_entries(char **args, size_t *entry_i, char *pattern)
{
	struct dirent	*entry;
	DIR				*cur_dir;

	cur_dir = opendir(".");
	if (!cur_dir)
		return (perror("Failed to open directory"));
	entry = readdir(cur_dir);
	while (entry)
	{
		if (entry_pattern_match(entry->d_name, pattern))
		{
			if (include_hidden(pattern[0], entry->d_name))
				args[(*entry_i)++] = strdup(entry->d_name);
		}
		entry = readdir(cur_dir);
	}
	closedir(cur_dir);
}

char	**wildcard_expansion(char **args, t_token *token)
{
	char	**expanded;
	size_t	args_count;
	size_t	i;
	size_t	entry_i;

	args_count = entries_count(args);
	if (!args_count)
		return (args);
	expanded = gc_malloc(sizeof(char *) * (args_count + 2), 1);
	if (!expanded)
		return (perror("Malloc"), NULL);
	i = -1;
	entry_i = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '*') == NULL || token->expand_wild
			|| !entry_count(args[i]))
			expanded[entry_i++] = ft_strdup(args[i]);
		else
			expand_arg_entries(expanded, &entry_i, args[i]);
		if (token)
			token = token->next;
	}
	expanded[entry_i] = NULL;
	return (expanded);
}
