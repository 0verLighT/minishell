/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 03:12:54 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/18 03:47:24 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Check if there's a redir token, add it, return 1 if went well
static int	handle_redirection_token(t_parser *parser, t_ast_node **cmd_node)
{
	*cmd_node = ensure_cmd_node_exists(*cmd_node);
	if (!*cmd_node)
		return (-1);
	if (parse_redirection(parser, *cmd_node) == -1)
		return (-1);
	return (1);
}

//Same as above but for words
static int	handle_word_token(t_parser *parser, char ***input,
							int *argc, int *capacity)
{
	t_token	*current;

	current = peek_token(parser, 0);
	if (add_word_to_input(input, argc, capacity, current->value) == -1)
		return (-1);
	advance(parser);
	return (1);
}

//We check what kind of token it is, and call the according func
int	handle_command_token(t_parser *parser, t_ast_node **cmd_node,
						char ***input, int *argc, int *capacity)
{
	t_token	*current;
	int		returned_value;

	current = peek_token(parser, 0);
	if (is_command_end(current))
		return (0);
	if (is_redirection(current))
	{
		returned_value = handle_redirection_token(parser, cmd_node);
		return (returned_value);
	}
	if (current->type == TOKEN_WORD)
	{
		returned_value = handle_word_token(parser, input, argc, capacity;
		return (returned_value);
	}
	advance(parser);
	returned_value = 1;
	return (returned_value);
}

//Gives the input to the cmd_node, finalizing it for exec use
static t_ast_node	*finalize_command_node(t_ast_node *cmd_node,
									char **input, int argc)
{
	if (argc == 0)
	{
		cleanup_on_error(cmd_node, input, argc);
		ft_putendl_fd("bash: syntax error: expected command", 2);
		return (NULL);
	}
	input[argc] = NULL;
	if (!cmd_node)
		return (create_cmd_node(input, NULL));
	cmd_node->data.cmd.input = input;
	return (cmd_node);
}

//Parses a simple command with args and redirections, then returns it
//10 capacity is an arbitrary choice, realistic number of args for a word
t_ast_node	*parse_simple_command(t_parser *parser)
{
	t_ast_node	*cmd_node;
	t_ast_node	*returned_nodes_list;
	char		**input;
	int			argc;
	int			capacity;
	int			result;

	cmd_node = NULL;
	capacity = 10;
	argc = 0;
	input = malloc(sizeof(char *) * capacity);
	if (!input)
		return (NULL);
	while (parser->current < parser->token_count)
	{
		result = handle_command_token(parser, &cmd_node,
									&input, &argc, &capacity);
		if (result == 0)
			break ;
		if (result == -1)
		{
			cleanup_on_error(cmd_node, input, argc);
			return (NULL);
		}
	}
	returned_nodes_list = finalize_command_node(cmd_node, input, argc);
	return (returned_nodes_list);
}
