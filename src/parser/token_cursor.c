/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:18:54 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/20 03:00:13 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Initialize the parser with tokens
void	init_parser(t_parser *parser, t_token *tokens, int token_count)
{
	parser->tokens = tokens;
	parser->token_count = token_count;
	parser->current = 0;
}

//Used to peek at a token at offset index
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

// Consume current token and move to next
// Returns the consumed token
t_token	*advance(t_parser *parser)
{
	t_token	*consumed;

	if (parser->current >= parser->token_count)
		return (NULL);
	consumed = &parser->tokens[parser->current];
	parser->current++;
	return (consumed);
}

//Allows to either check if the token match a type
//And then either peek or consume it
//Return 1 if match
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

//Expect a specific token type, consume it or report error
//Returns true if token matched and consumed, false on error
int	expect_token(t_parser *parser, t_token_type type, char *error_msg)
{
	t_token	*current;

	current = peek_token(parser, 0);
	if (!current)
	{
		printf("Syntax error: unexpected end of input. %s\n", error_msg);
		return (0);
	}
	if (current->type != type)
	{
		printf("Syntax error: %s (got '%s')\n", error_msg, current->value);
		return (0);
	}
	advance(parser);
	return (1);
}
