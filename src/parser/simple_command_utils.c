/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 04:44:46 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/30 23:17:54 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_command_end(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR || token->type == TOKEN_EOF)
		return (1);
	return (0);
}

char	**expand_input_array(char **input, int capacity)
{
	char	**new_input;
	int		i;

	new_input = malloc(sizeof(char *) * (capacity * 2));
	if (!new_input)
		return (NULL);
	i = 0;
	while (i < capacity)
	{
		new_input[i] = input[i];
		i++;
	}
	free(input);
	capacity *= 2;
	return (new_input);
}

int	add_word_to_input(char **input, int argc, int capacity, char *word)
{
	if (argc >= capacity - 1)
	{
		input = expand_input_array(input, capacity);
		if (!input)
			return (-1);
	}
	input[argc] = ft_strdup(word);
	if (!input[argc])
		return (-1);
	++argc;
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
