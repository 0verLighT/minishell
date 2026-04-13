/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 04:44:46 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/13 16:58:05 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_command_end(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == TOKEN_PIPE
		|| token->type == TOKEN_AND
		|| token->type == TOKEN_OR
		|| token->type == TOKEN_EOF
		|| token->type == TOKEN_RPAREN
	)
		return (1);
	return (0);
}

char	**expand_input_array(t_cmd_ctx *ctx)
{
	char	**new_input;
	int		i;

	new_input = ft_calloc(sizeof(char *), ctx->capacity * 2);
	if (!new_input)
		return (NULL);
	i = 0;
	while (i < ctx->capacity)
	{
		new_input[i] = ctx->input[i];
		++i;
	}
	free(ctx->input);
	ctx->capacity *= 2;
	return (new_input);
}

int	add_word_to_input(t_cmd_ctx *ctx, char *word)
{
	if (ctx->argc >= ctx->capacity - 1)
	{
		ctx->input = expand_input_array(ctx);
		if (!ctx->input)
			return (-1);
	}
	ctx->input[ctx->argc] = ft_strdup(word);
	if (!ctx->input[ctx->argc])
		return (-1);
	++ctx->argc;
	return (0);
}

t_ast_node	*ensure_cmd_node_exists(t_ast_node *cmd_node)
{
	t_ast_node	*returned_node;

	if (cmd_node)
		return (cmd_node);
	returned_node = create_cmd_node(NULL, NULL);
	return (returned_node);
}

void	free_cmd_ctx(t_cmd_ctx *ctx)
{
	if (ctx->cmd_node)
		free_ast_node(ctx->cmd_node);
	if (ctx->input)
		free_array(ctx->input);
	free(ctx);
}
