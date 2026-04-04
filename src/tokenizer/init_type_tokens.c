/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:05:23 by amartel           #+#    #+#             */
/*   Updated: 2026/04/04 03:43:31 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

/**
 * @brief get index in enum of token type
 * @param token
 * @param i
 * @return index of token type
 */
static int	get_type_of_token(char *ptr)
{
	if (ft_strncmp(ptr, "<<", 2) == 0)
		return (4);
	else if (ft_strncmp(ptr, ">>", 2) == 0)
		return (5);
	else if (ptr == '&' || ft_strncmp(ptr, "&&", 2) == 0)
		return (6);
	else if (ft_strncmp(ptr, "||", 2) == 0)
		return (7);
	else if (ptr == '|')
		return (1);
	else if (ptr == '<')
		return (2);
	else if (ptr == '>')
		return (3);
	else if (ptr == '(')
		return (8);
	else if (ptr == ')')
		return (9);
	else if (ptr == '\0')
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
		tokens[i].type = get_type_of_token(tokens[i].content.ptr);
		++i;
	}
}
