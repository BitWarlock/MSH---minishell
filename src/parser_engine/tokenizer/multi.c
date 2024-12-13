/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:53:39 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/01 22:16:58 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*operator(char *word)
{
	if (word[0] == '&' && word[1] == '&')
		return (ft_substr("&&", 0, 2));
	else if (word[0] == '|' && word[1] == '|')
		return (ft_substr("||", 0, 2));
	else if (word[0] == '|')
		return (ft_substr("|", 0, 1));
	else if (word[0] == '>' && word[1] == '>')
		return (ft_substr(">>", 0, 2));
	else if (word[0] == '>')
		return (ft_substr(">", 0, 1));
	else if (word[0] == '<' && word[1] == '<')
		return (ft_substr("<<", 0, 2));
	else if (word[0] == '<')
		return (ft_substr("<", 0, 1));
	return (NULL);
}

static char	*extract(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !operator(&str[i])
		&& str[i] != '('
		&& str[i] != ')')
		i++;
	return (ft_substr(str, 0, i));
}

void	multi(char *word, t_token **token_list)
{
	t_token		*node;
	size_t		i;
	char		*str;

	i = 0;
	while (word[i])
	{
		str = operator(&word[i]);
		if (word[i] == '(')
			str = ft_substr("(", 0, 1);
		else if (word[i] == ')')
			str = ft_substr(")", 0, 1);
		else if (!str)
			str = extract(&word[i]);
		node = init_node(str);
		append(node, token_list);
		i += ft_strlen(str);
	}
}
