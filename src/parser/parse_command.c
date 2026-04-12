/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 03:23:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/12 05:03:27 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_redirection_token(t_parser *parser, t_ast_node *cmd_node)
{
	cmd_node = ensure_cmd_node_exists(cmd_node);
	if (!cmd_node)
		return (-1);
	if (parse_redirection(parser, cmd_node) == -1)
		return (-1);
	return (1);
}

int	handle_word_token(t_parser *parser, t_cmd_ctx *ctx)
{
	t_token	*current;

	current = peek_token(parser, 0);
	if (add_word_to_input(ctx, current->content.ptr) == -1)
		return (-1);
	advance(parser);
	return (1);
}

t_ast_node	*finalize_command_node(t_cmd_ctx *ctx, t_parser *parser)
{
	const char	*line_error = "minishel: syntax error near unexpected token";

	if (ctx->argc == 0)
	{
		free_cmd_ctx(ctx);
		if (parser->tokens->type == TOKEN_PIPE)
			ft_dprintf(2, "%s `|'\n", line_error);
		else if (parser->tokens->type == TOKEN_AND)
			ft_dprintf(2, "%s `&'\n", line_error);
		else if (parser->tokens->type == TOKEN_RPAREN)
			ft_dprintf(2, "%s `)'\n", line_error);
		return (NULL);
	}
	ctx->input[ctx->argc] = NULL;
	if (!ctx->cmd_node)
		return (create_cmd_node(ctx->input, NULL));
	ctx->cmd_node->data.cmd.input = ctx->input;
	return (ctx->cmd_node);
}

int	process_command_tokens(t_parser *parser, t_cmd_ctx *ctx)
{
	int	result;

	while (parser->current < parser->token_count)
	{
		result = handle_command_token(parser, ctx);
		if (result == 0)
			break ;
		if (result == -1)
			return (-1);
	}
	return (0);
}

t_ast_node	*parse_simple_command(t_parser *parser)
{
	t_cmd_ctx	*ctx;
	t_ast_node	*node;

	ctx = malloc(sizeof(t_cmd_ctx));
	if (!ctx)
		return (NULL);
	ctx->cmd_node = NULL;
	ctx->argc = 0;
	ctx->capacity = 10;
	ctx->input = malloc(sizeof(char *) * ctx->capacity);
	if (!ctx->input)
		return (NULL);
	if (process_command_tokens(parser, ctx) == -1)
	{
		free_cmd_ctx(ctx);
		return (NULL);
	}
	node = finalize_command_node(ctx, parser);
	free(ctx);
	return (node);
}
