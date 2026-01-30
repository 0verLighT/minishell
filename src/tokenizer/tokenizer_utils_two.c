/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:33:13 by jdessoli          #+#    #+#             */
/*   Updated: 2026/01/26 02:42:14 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//Get the length of a token starting at pos
int	get_token_len(char *str, int pos)
{
	int	len;
	
	len = 0;
	while (!is_space(str[pos]) && str[pos])
	{
		len++;
		pos++;
	}
	return (len);
}

//Allocate and fill a token
int	fill_token(t_token *token, char *str, int pos, int index)
{
	int	len;
	
	len = get_token_len(str, pos);
	token->index = index;
	token->content.len = len;
	token->content.ptr = malloc(len + 1);
	if (!token->content.ptr)
		return (0);
	ft_memcpy(token->content.ptr, str + pos, len);
	token->content.ptr[len] = '\0';
	return (1);
}

//Init a sentinel token at the end of the array
//It's used to put an end to the string, like a 0
void	init_sentinel(t_token *token)
{
	token->index = -1;
	token->content.ptr = NULL;
	token->content.len = 0;
}

// Fill the tokens one by one
int	process_tokens(t_token *tokens, char *str, int token_count)
{
	int	i;
	int	pos;
	
	i = 0;
	pos = 0;
	while (i < token_count)
	{
		pos += strskip(str + pos, " \t\n");
		if (!fill_token(&tokens[i], str, pos, i))
		{
			free_tokens(tokens);
			return (0);
		}
		pos += tokens[i].content.len;
		i++;
	}
	return (1);
}

t_token	*tokenizing(char *str)
{
	t_token	*tokens;
	int		token_count;
	
	if (!str)
		return (NULL);
	token_count = count_token(str);
	tokens = malloc(sizeof(t_token) * (token_count + 1));
	if (!tokens)
		return (NULL);
	if (!process_tokens(tokens, str, token_count))
		return (NULL);
	init_sentinel(&tokens[token_count]);
	return (tokens);
}
