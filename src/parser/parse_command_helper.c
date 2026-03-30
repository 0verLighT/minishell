/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 03:23:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/30 20:38:51 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_redirection_token(t_parser *parser, t_ast_node **cmd_node)
{
	*cmd_node = ensure_cmd_node_exists(*cmd_node);
	if (!*cmd_node)
		return (-1);
	if (parse_redirection(parser, *cmd_node) == -1)
		return (-1);
	return (1);
}

int	handle_word_token(t_parser *parser, char ***input,
						int *argc, int *capacity)
{
	t_token	*current;

	current = peek_token(parser, 0);
	if (add_word_to_input(input, argc, capacity, current->content.ptr) == -1)
		return (-1);
	advance(parser);
	return (1);
}

t_ast_node	*finalize_command_node(t_ast_node *cmd_node,
									char **input, int argc)
{
	if (argc == 0)
	{
		cleanup_on_error(cmd_node, input);
		ft_dprintf(2, "minishell: syntax error: expected command\n");
		return (NULL);
	}
	input[argc] = NULL;
	if (!cmd_node)
		return (create_cmd_node(input, NULL));
	cmd_node->data.cmd.input = input;
	return (cmd_node);
}

//Used to build the command structure
/**
 * @brief Build the command struture
 * @param paser
 * @return -1 on error, 0 on successfully
 */
static int	process_command_tokens(t_parser *parser)
{
	int	result;

	while (parser->current < parser->token_count)
	{
		result = handle_command_token(parser);
		if (result == 0)
			break ;
		if (result == -1)
			return (-1);
	}
	return (0);
}

t_ast_node	*parse_simple_command(t_parser *parser)
{
	t_cmd_ctx *ctx;

	ctx = malloc(sizeof(t_cmd_ctx));
	if (!ctx)
		return (NULL);
	ctx->cmd_node = NULL;
	ctx->argc = 0;
	ctx->capacity = 10;
	ctx->input = malloc(sizeof(char *) * ctx->capacity);
	if (!ctx->input)
		return (NULL);
		
	if (process_command_tokens(parser) == -1)
	{
		cleanup_on_error(ctx->cmd_node, ctx->input);
		return (NULL);
	}
	return (finalize_command_node(ctx->cmd_node, ctx->input, ctx->argc));
}
