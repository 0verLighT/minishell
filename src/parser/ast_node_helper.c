/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:52:47 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/20 02:57:53 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Create a command node with its type, args and redir
t_ast_node	*create_cmd_node(char **input, t_redirect *redirects)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->data.cmd.input = input;
	node->data.cmd.redirects = redirects;
	return (node);
}

//Create a pipe node
t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);
}

//Create an AND node
t_ast_node	*create_and_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_AND;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);
}

//Create an OR node
t_ast_node	*create_or_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_OR;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);
}
