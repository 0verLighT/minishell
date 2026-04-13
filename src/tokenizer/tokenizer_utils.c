/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:21:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/13 16:58:16 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_tokens(t_token *tokens, size_t token_nb)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (i < token_nb)
		free(tokens[i++].content.ptr);
	free(tokens);
	return ;
}

size_t	strskip(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		++i;
	return (i);
}

size_t	count_token(char *str)
{
	size_t	token_nb;
	size_t	i;
	size_t	len;
	size_t	_;

	token_nb = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (ft_isspace(str[i]) && str[i])
			++i;
		if (str[i])
		{
			token_nb++;
			len = get_token_len(str, i, &_, NULL);
			i += len;
		}
	}
	return (token_nb);
}

t_node_token	*token_maker(char *str)
{
	t_node_token	*token;
	size_t			token_start;
	size_t			len;

	if (!str)
		return (NULL);
	token = ft_calloc(sizeof(t_node_token), 1);
	if (!token)
		return (NULL);
	token_start = strskip(str);
	len = token_start;
	while (!ft_isspace(str[len]) && str[len])
		len++;
	token->len = len - token_start;
	token->ptr = ft_calloc((token->len + 1), sizeof(char));
	if (!token->ptr)
	{
		free(token);
		return (NULL);
	}
	ft_memcpy(token->ptr, str + token_start, token->len);
	return (token);
}

char	*create_token(char *str, size_t pos, size_t len, size_t content_len)
{
	size_t	i;
	size_t	j;
	int		quote;
	char	*token;

	quote = 0;
	i = 0;
	j = 0;
	token = ft_calloc((content_len + 1), sizeof(char));
	if (!token)
		return (0);
	while (i < len)
	{
		if ((str[pos + i] == '"' || str[pos + i] == '\'') && !quote)
			quote = str[pos + i++];
		else if (quote && str[pos + i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			token[j++] = str[pos + i++];
	}
	return (token);
}
