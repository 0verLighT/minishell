/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 01:06:01 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/18 01:20:26 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Checks if current token is a pipe operator
static int	is_pipe_operator(t_parser *parser)
{
	t_token	*token;

	token = peek_token(parser, 0);
	if (!token)
		return (0);
	return (token->type == TOKEN_PIPE);
}

//Check if pipe's at valid pos (neither at start nor end of input)
static int	validate_pipe_position(t_parser *parser, t_ast_node *left)
{
	t_token	*next;

	if (!left)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		return (0);
	}
	next = peek_token(parser, 1);
	if (!next || next->type == TOKEN_EOF || next->type == TOKEN_PIPE)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		return (0);
	}
	return (1);
}

//Parses what's after the pipe
static t_ast_node	*parse_pipe_right_side(t_parser *parser)
{
	advance(parser);
	return (parse_pipeline(parser));
}

//Creates a pipeline node connecting left and right commands
static t_ast_node	*create_pipeline(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*result;

	result = NULL;
	if (!right)
		free_ast_node(left);
	else
		result = create_pipe_node(left, right);
	return (result);
}

//Parses an input with multiple pipes
//Returns root of pipeline tree
t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*left;
	t_ast_node	*right;
	int			valid;

	left = parse_simple_command(parser);
	while (left && is_pipe_operator(parser))
	{
		valid = validate_pipe_position(parser, left);
		if (!valid)
		{
			free_ast_node(left);
			left = NULL;
		}
		else
		{
			right = parse_pipe_right_side(parser);
			left = create_pipeline(left, right);
		}
	}
	return (left);
}
