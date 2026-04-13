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

static size_t	get_token_len_helper(char *str, size_t pos,
		size_t *content_len, t_token *token)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (str[pos + len])
	{
		if ((str[pos + len] == '"' || str[pos + len] == '\'') && !quote)
		{
			quote = str[pos + len];
			if (token)
				token->content.quote = 1;
		}
		else if (quote && str[pos + len] == quote)
			quote = 0;
		else if (!quote && (ft_isspace(str[pos + len])
				|| isoperator(str[pos + len])))
			break ;
		else
			++(*content_len);
		++len;
	}
	return (len);
}

size_t	get_token_len(char *str, size_t pos,
			size_t *content_len, t_token *token)
{
	size_t	len;

	len = 0;
	*content_len = 0;
	if (isdoubleop(&str[pos]))
	{
		*content_len = 2;
		return (2);
	}
	if (isoperator(str[pos]))
	{
		*content_len = 1;
		return (1);
	}
	len += get_token_len_helper(str, pos, content_len, token);
	return (len);
}

int	fill_token(t_token *token, char *str, size_t *pos, int index)
{
	size_t	len;
	size_t	content_len;

	token->content.quote = 0;
	len = get_token_len(str, *pos, &content_len, token);
	token->index = index;
	token->content.len = content_len;
	token->content.ptr = create_token(str, *pos, len, content_len);
	if (!token->content.ptr)
		return (0);
	*pos += len;
	return (1);
}

int	init_tokens(t_token *tokens, char *str, size_t token_count)
{
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	while (i < token_count)
	{
		pos += strskip(str + pos);
		if (!fill_token(&tokens[i], str, &pos, i))
		{
			free_tokens(tokens, token_count);
			return (0);
		}
		++i;
	}
	return (1);
}

t_token	*tokenizing(char *str, size_t *token_count)
{
	t_token		*tokens;

	if (!str)
		return (NULL);
	*token_count = count_token(str);
	tokens = ft_calloc((*token_count + 1), sizeof(t_token));
	if (!tokens)
		return (NULL);
	if (!init_tokens(tokens, str, *token_count))
	{
		free(tokens);
		return (NULL);
	}
	return (tokens);
}
