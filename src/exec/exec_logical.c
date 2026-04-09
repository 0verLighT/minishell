/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:37:32 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 17:43:08 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Mimic && by executing left node first, even if right fail
 * @param node
 * @param ctx
 * @return If both succed, right is returned
 */
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

/**
 * @brief Mimic || so that right only runs if left fail
 * @param node
 * @param ctx
 */
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
