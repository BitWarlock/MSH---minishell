/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 08:01:01 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/07 08:01:03 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	*new_arr(char **args)
{
	size_t	len;
	int		*arr;

	len = args_len(args);
	arr = gc_malloc(sizeof(int) * len, 1);
	if (!arr)
		return (NULL);
	return (arr);
}

int	new_args_len(char **args, int *is_null)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (!is_null[i])
			len++;
		i++;
	}
	return (len);
}

char	**remove_null_values(char **args, int *is_null)
{
	char	**new_args;
	int		len_args_new;
	int		i;
	int		j;

	len_args_new = new_args_len(args, is_null);
	if (len_args_new == args_len(args))
		return (args);
	new_args = gc_malloc(sizeof(char *) * (len_args_new + 1), 1);
	if (!new_args)
		return (perror("malloc"), NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (!is_null[i])
			new_args[j++] = args[i];
		i++;
	}
	new_args[len_args_new] = NULL;
	return (new_args);
}

char	*copy_char(int *i, char *var, char *result)
{
	char	*tmp;

	tmp = ft_substr(var, *i, 1);
	result = ft_strjoin(result, tmp);
	if (!result)
		return (perror("Malloc"), NULL);
	(*i)++;
	return (result);
}
