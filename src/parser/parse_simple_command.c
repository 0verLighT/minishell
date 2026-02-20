/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 03:12:54 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/20 04:45:20 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Store pointers in static variables for use by handle_command_token
void	set_command_context(t_ast_node **cmd_node, char ***input,
								int *argc, int *capacity)
{
	static t_ast_node	**g_cmd_node;
	static char			***g_input;
	static int			*g_argc;
	static int			*g_capacity;

	g_cmd_node = cmd_node;
	g_input = input;
	g_argc = argc;
	g_capacity = capacity;
}

//Get the stored cmd_node pointer
static t_ast_node	**get_cmd_node(void)
{
	static t_ast_node	**g_cmd_node;

	return (g_cmd_node);
}

//Get all input-related pointers at once
static void	get_input_context(char ****input, int **argc, int **capacity)
{
	static char	***g_input;
	static int	*g_argc;
	static int	*g_capacity;

	*input = g_input;
	*argc = g_argc;
	*capacity = g_capacity;
}

//Process token based on type (redirection or word)
static int	process_token(t_parser *parser, t_token *current)
{
	char	***input;
	int		*argc;
	int		*capacity;
	int		result;

	if (is_redirection(current))
	{
		result = handle_redirection_token(parser, get_cmd_node());
		return (result);
	}
	if (current->type == TOKEN_WORD)
	{
		get_input_context(&input, &argc, &capacity);
		result = handle_word_token(parser, input, argc, capacity);
		return (result);
	}
	advance(parser);
	return (1);
}

//We check what kind of token it is, and call the according func
int	handle_command_token(t_parser *parser)
{
	t_token	*current;
	int		result;

	current = peek_token(parser, 0);
	if (is_command_end(current))
		return (0);
	result = process_token(parser, current);
	return (result);
}
