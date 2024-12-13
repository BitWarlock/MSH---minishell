/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expansion_indices.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/09 00:30:35 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	set_indices(t_token *token, size_t var_count, size_t i, size_t j)
{
	int		is_quoted_rslt;

	token->expansion_indices = gc_malloc(sizeof(size_t) * var_count, COLLECT);
	ft_memset(token->expansion_indices, 0, sizeof(size_t) * var_count);
	while (token->word[i])
	{
		is_quoted_rslt = is_quoted(token->word[i]);
		if ((is_quoted_rslt == '"' || is_quoted_rslt == 0)
			&& token->word[i] == '$')
		{
			if (!is_quoted_rslt)
				token->expansion_indices[j] = 2;
			if (is_quoted_rslt && token->word[i + 1]
				&& token->word[i + 1] != '"')
				token->expansion_indices[j] = 3;
			else if ((token->word[i] == '$' && token->word[i + 1]
					&& token->word[i + 1] != '"' && token->word[i + 1] != '\''))
				token->expansion_indices[j] = 1;
			j++;
		}
		else if (is_quoted_rslt == '\'' && token->word[i] == '$')
			j++;
		i++;
	}
}

void	set_expansion_indices(t_token *token)
{
	size_t	var_count;
	size_t	i;
	size_t	j;
	size_t	e;

	var_count = 0;
	i = 0;
	while (token->word[i])
		if (token->word[i++] == '$')
			var_count++;
	if (!var_count)
		return ;
	j = 0;
	e = 0;
	set_indices(token, var_count, j, e);
}

void	set_tokens_expansion_indices(t_token *tokens)
{
	while (tokens)
	{
		if ((ft_strchr(tokens->word, '\'') || ft_strchr(tokens->word, '"'))
			&& (tokens->type == ARGUMENT || tokens->type == COMMAND))
			tokens->expand_wild = 69420;
		if (tokens->type == LIMITER && (!ft_strchr(tokens->word, '\'')
				&& !ft_strchr(tokens->word, '"')))
			tokens->expansion_indices[0] = 1;
		else
			set_expansion_indices(tokens);
		tokens = tokens->next;
	}
}
