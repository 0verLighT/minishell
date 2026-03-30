/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 03:12:54 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/30 22:48:20 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Get the stored cmd_node pointer
 * @return the command in the node
 */
static t_ast_node	**get_cmd_node(void)
{
	static t_ast_node	**g_cmd_node;

	return (g_cmd_node);
}

/**
 * @brief Process token based on type (redirection or word)
 * @return 
 */
static int	process_token(t_parser *parser, t_token *current, t_cmd_ctx *ctx)
{
	int result;

	if (is_redirection(current))
	{
		result = handle_redirection_token(parser, get_cmd_node());
		return (result);
	}
	if (current->type == TOKEN_WORD)
	{
		result = handle_word_token(parser, ctx);
		return (result);
	}
	advance(parser);
	return (1);
}

int	handle_command_token(t_parser *parser, t_cmd_ctx *ctx)
{
	t_token	*current;
	int		result;

	current = peek_token(parser, 0);
	if (is_command_end(current))
		return (0);
	result = process_token(parser, current, ctx);
	return (result);
}
