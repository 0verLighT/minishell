/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:33:3 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/26 01:47:34 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//Get the length of a token starting at pos
size_t	get_token_len(char *str, int pos)
{
	size_t	len;

	len = 0;
	if (isdoubleop(str + pos))
		return (2);
	if (isoperator(str[pos]))
		return (1);
	while (str[pos + len] && !ft_isspace(str[pos + len]) && 
		!isoperator(str[pos + len]))
		len++;
	return (len);
}

//Allocate and fill a token
int	fill_token(t_token *token, char *str, int pos, int index)
{
	size_t	len;

	len = get_token_len(str, pos);
	token->index = index;
	token->content.len = len;
	token->content.ptr = ft_calloc((len + 1), sizeof(char));
	if (!token->content.ptr)
		return (0);
	ft_memcpy(token->content.ptr, str + pos, len);
	token->content.ptr[len] = '\0';
	return (1);
}

// Fill the tokens one by one
size_t	process_tokens(t_token *tokens, char *str, size_t token_count)
{
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	while (i < token_count)
	{
		pos += strskip(str + pos);
		if (!fill_token(&tokens[i], str, pos, i))
		{
			free_tokens(tokens);
			return (0);
		}
		pos += tokens[i++].content.len;
	}
	return (1);
}

t_token	*tokenizing(char *str)
{
	t_token	*tokens;
	size_t	token_count;

	if (!str)
		return (NULL);
	token_count = count_token(str);
	tokens = ft_calloc((token_count + 1), sizeof(t_token));
	if (!tokens)
		return (NULL);
	if (!process_tokens(tokens, str, token_count))
		return (NULL);
	return (tokens);
}
