/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:05:23 by amartel           #+#    #+#             */
/*   Updated: 2026/04/05 00:50:56 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/**
 * @brief get index in enum of token type
 * @param token
 * @param i
 * @return index of token type
 */
static int	get_type_of_token(t_token *token, size_t i)
{
	if (ft_strncmp(token[i].content.ptr, "<<", 2) == 0)
		return (4);
	else if (ft_strncmp(token[i].content.ptr, ">>", 2) == 0)
		return (5);
	else if (*token[i].content.ptr == '&'
		|| ft_strncmp(token[i].content.ptr, "&&", 2) == 0)
		return (6);
	else if (ft_strncmp(token[i].content.ptr, "||", 2) == 0)
		return (7);
	else if (*token[i].content.ptr == '|')
		return (1);
	else if (*token[i].content.ptr == '<')
		return (2);
	else if (*token[i].content.ptr == '>')
		return (3);
	else if (*token[i].content.ptr == '(')
		return (8);
	else if (*token[i].content.ptr == ')')
		return (9);
	else if (*token[i].content.ptr == '\0')
		return (10);
	else
		return (0);
}

void	init_type_tokens(t_token *tokens, size_t token_count)
{
	size_t	i;

	i = 0;
	while (i < token_count)
	{
		tokens[i].type = get_type_of_token(tokens, i);
		++i;
	}
}
