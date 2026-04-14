/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 20:01:53 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/14 04:04:37 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Saves the current fd, run the builtin, then restore fd
 * @details The saving is needed because some bultin like export modify
 * shell state
 * @param node
 * @param ctx
 */
static int	run_builtin_in_parent(t_ast_node *node, t_ctx *ctx)
{
	t_fdsave	fdsave;
	int			ret;

	if (apply_redirections(node->data.cmd.redirects, &fdsave, ctx))
		return (FAIL);
	ret = exec_builtin(node->data.cmd.input, ctx);
	restore_fds(&fdsave);
	return (ret);
}

/**
 * @brief fork then apply a redir or builtin in the child process
 * @param node
 * @param ctx
 */
static int	run_in_child(t_ast_node *node, t_ctx *ctx)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (FAIL);
	}
	if (pid == 0)
	{
		if (apply_redirections(node->data.cmd.redirects, NULL, ctx))
		{
			ctx->return_code = 1;
			exit(FAIL);
		}
		if (is_builtin(node->data.cmd.input[0]))
			exit(exec_builtin(node->data.cmd.input, ctx));
		exit(exec_external(node->data.cmd.input, ctx));
	}
	ret = exec_wait(pid, ctx);
	return (ret);
}

int	exec_cmd(t_ast_node *node, t_ctx *ctx)
{
	int	ret_parent;
	int	ret_child;

	if (!node->data.cmd.input || !node->data.cmd.input[0])
		return (SUCCESS);
	if (is_builtin(node->data.cmd.input[0]))
	{
		ret_parent = run_builtin_in_parent(node, ctx);
		return (ret_parent);
	}
	ret_child = run_in_child(node, ctx);
	return (ret_child);
}
