/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:21:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/01/31 03:43:57 by amartel          ###   ########.fr       */
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

size_t	strskip(char *str, char *charset)
{
	size_t	i;
	size_t	j;
	size_t	found;

	i = 0;
	while (str[i])
	{
		j = 0;
		found = 0;
		while (charset[j])
		{
			if (charset[j] == str[i])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			break ;
		i++;
	}
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
			i++;
		if (str[i] != 0)
		{
			token_nb++;
			while (!ft_isspace(str[i]) && str[i])
				i++;
		}
	}
	return (token_nb);
}

t_slice	*token_maker(char *str)
{
	t_slice	*token;
	size_t	token_start;
	size_t	len;

	if (!str)
		return (NULL);
	token = malloc(sizeof(t_slice));
	if (!token)
		return (NULL);
	token_start = strskip(str, " \t\n");
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
