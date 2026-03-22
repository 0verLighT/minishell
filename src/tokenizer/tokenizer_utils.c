/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:21:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/22 23:50:13 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	free_tokens(t_token *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].index)
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
	size_t	i;
	size_t	token_nb;

	i = 0;
	token_nb = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (ft_isspace(str[i]) && str[i])
			++i;
		token_nb++;
		if (isdoubleop(str + i))
			i += 2;
		else if (isoperator(str[i]))
			++i;
		else
		{
			while (!ft_isspace(str[i]) && str[i] && !isoperator(str[i]))
				++i;
		}
	}
	return (token_nb);
}

t_node_token	*token_maker(char *str)
{
	t_node_token	*token;
	size_t	token_start;
	size_t	len;

	if (!str)
		return (NULL);
	token = malloc(sizeof(t_node_token));
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
