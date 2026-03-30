/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:18:54 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/29 03:08:09 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_parser(t_parser *parser, t_token *tokens, int token_count)
{
	parser->tokens = tokens;
	parser->token_count = token_count;
	parser->current = 0;
}

t_token	*peek_token(t_parser *parser, int offset)
{
	int	target_index;

	target_index = parser->current + offset;
	if (target_index < 0)
		return (NULL);
	if (target_index >= parser->token_count)
		return (NULL);
	return (&parser->tokens[target_index]);
}

t_token	*advance(t_parser *parser)
{
	t_token	*consumed;

	if (parser->current >= parser->token_count)
		return (NULL);
	consumed = &parser->tokens[parser->current];
	++parser->current;
	return (consumed);
}

int	match_token(t_parser *parser, t_token_type type, int consume)
{
	t_token	*current;

	current = peek_token(parser, 0);
	if (!current)
		return (0);
	if (current->type != type)
		return (0);
	if (consume)
		advance(parser);
	return (1);
}

int	expect_token(t_parser *parser, t_token_type type, char *err_msg)
{
	t_token	*current;
	char	*content;

	current = peek_token(parser, 0);
	if (!current)
	{
		ft_dprintf(2, "Syntax error: unexpected end of input. %s\n", err_msg);
		return (0);
	}
	if (current->type != type)
	{
		content = current->content.ptr;
		ft_dprintf(2, "Syntax error: %s (got '%s')\n", err_msg, content);
		return (0);
	}
	advance(parser);
	return (1);
}
