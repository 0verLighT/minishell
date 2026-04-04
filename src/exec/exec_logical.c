/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:37:32 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 19:44:08 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Mimic && by executing left node first, even if right fail
//if both succeed right is returned
//if needed, check parser.h for the node struct
static int	exec_and(t_ast_node *node, t_ctx *ctx)
{
	int	ret_left;
	int	ret_right;

	ret_left = exec_node(node->data.pair.left, ctx);
	if (ret_left != SUCCESS)
		return (ret_left);
	ret_right = exec_node(node->data.pair.right, ctx);
	return (ret_right);
}

//Mimic || so that right only runs if left fail
static int	exec_or(t_ast_node *node, t_ctx *ctx)
{
	int	left_ret;
	int	right_ret;

	left_ret = exec_node(node->data.pair.left, ctx);
	if (left_ret == SUCCESS)
		return (left_ret);
	right_ret = exec_node(node->data.pair.right, ctx);
	return (right_ret);
}

//dispatcher of the two above
int	exec_logical(t_ast_node *node, t_ctx *ctx)
{
	int	ret_and;
	int	ret_or;

	if (node->type == NODE_AND)
	{
		ret_and = exec_and(node, ctx);
		return (ret_and);
	}
	ret_or = exec_or(node, ctx);
	return (ret_or);
}
