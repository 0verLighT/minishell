/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 01:06:01 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/03 03:22:08 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Checks if current token is a pipe operator
 * @param parser
 * @return The type code of token
 */
static int	is_pipe_operator(t_parser *parser)
{
	t_token	*token;

	token = peek_token(parser, 0);
	if (!token)
		return (0);
	return (token->type == TOKEN_PIPE);
}
//! next is always NULL atfer -> `ls |` OR `ls &`
/**
 * @brief Check if pipe's at valid pos
 * @details (neither at start nor end of input)
 * @param parser
 * @param left
 * @return 0 on error, 1 on successfully
 */
static int	validate_pipe_position(t_parser *parser, t_ast_node *left)
{
	t_token	*next;

	if (!left)
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	next = peek_token(parser, 1);
	if (!next || next->type == TOKEN_EOF || next->type == TOKEN_PIPE)
	{
		ft_dprintf(2, "minishell: syntax error :(\n");
		return (0);
	}
	return (1);
}

/**
 * @brief Pares content after the pipe
 * @param parser
 * @return node with content after the pipe
 */
static t_ast_node	*parse_pipe_right_side(t_parser *parser)
{
	advance(parser);
	return (parse_pipeline(parser));
}

/**
 * @brief Creates a pipeline node connecting left and right commands
 * @param left
 * @param right
 * @return node with new pipe
 */
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
