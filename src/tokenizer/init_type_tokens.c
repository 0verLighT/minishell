/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 19:05:23 by amartel           #+#    #+#             */
/*   Updated: 2026/03/31 23:29:17 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	init_type_tokens(t_token *tokens, size_t token_count)
{
	size_t	i;

	i = 0;
	while (i < token_count)
	{
		printf("%s\n", tokens[i].content.ptr);
		if (*tokens[i].content.ptr == '|')
			tokens[i].type = 1;
		else if (*tokens[i].content.ptr == '<')
			tokens[i].type = 2;
		else if (*tokens[i].content.ptr == '>')
			tokens[i].type = 3;
		else if (ft_strncmp(tokens[i].content.ptr, "<<", 2))
			tokens[i].type = 4;
		else if (ft_strncmp(tokens[i].content.ptr, ">>", 2))
			tokens[i].type = 5;
		else
			tokens[i].type = 0;
		++i;
	}
}
