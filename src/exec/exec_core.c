/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 21:49:48 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/03 21:55:27 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//asses what to call depending on the node type
static int	exec_dispatch(t_ast_node *node, t_ctx *ctx)
{
	int	ret;

	if (node->type == NODE_CMD)
	{
		ret = exec_cmd(node, ctx);
		return (ret);
	}
	if (node->type == NODE_PIPE)
	{
		ret = exec_pipe(node, ctx);
		return (ret);
	}
	if (node->type == NODE_AND || node->type == NODE_OR)
	{
		ret = exec_logical(node, ctx);
		return (ret);
	}
	return (FAIL);
}

//Entry point fo exec call. Call dispatch, then store return code
int	exec_node(t_ast_node *node, t_ctx *ctx)
{
	int	ret;

	if (!node || !ctx)
		return (FAIL);
	ret = exec_dispatch(node, ctx);
	ctx->return_code = ret;
	return (ret);
}
