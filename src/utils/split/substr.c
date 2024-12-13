/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:38:18 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/12 12:24:43 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../../../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		size;
	size_t		substr_len;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	substr_len = ft_strlen(s + start);
	if (substr_len < len)
		len = substr_len;
	size = sizeof(char) * (len + 1);
	substr = gc_malloc(size, COLLECT);
	if (!substr)
		return (0);
	ft_strlcpy(substr, &s[start], size);
	return (substr);
}
