/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 01:33:52 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/07 01:34:16 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//wrap pipe with perror, same logic as cd_core in builtin folder
static int	open_pipe(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (FAIL);
	}
	return (SUCCESS);
}

//Child process for redirecting the output of
//what's on the left side of the pipe
static void	run_left(t_ast_node *node, int fd[2], t_ctx *ctx)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(exec_node(node->data.pair.left, ctx));
}

//Child process for redirecting to the input of
//what's on the right side of the pipe
static void	run_right(t_ast_node *node, int fd[2], t_ctx *ctx)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(exec_node(node->data.pair.right, ctx));
}

//Fork process for the run left and right functions
static int	fork_children(t_ast_node *node, int fd[2],
				pid_t pids[2], t_ctx *ctx)
{
	pids[0] = fork();
	if (pids[0] < 0)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (FAIL);
	}
	if (pids[0] == 0)
		run_left(node, fd, ctx);
	pids[1] = fork();
	if (pids[1] < 0)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (FAIL);
	}
	if (pids[1] == 0)
		run_right(node, fd, ctx);
	close(fd[0]);
	close(fd[1]);
	return (SUCCESS);
}

//Orchestrate, then wait for left then right chidren,
//and return the last children exit code
int	exec_pipe(t_ast_node *node, t_ctx *ctx)
{
	int		fd[2];
	pid_t	pids[2];
	int		ret;

	if (open_pipe(fd))
		return (FAIL);
	if (fork_children(node, fd, pids, ctx))
		return (FAIL);
	exec_wait(pids[0], ctx);
	ret = exec_wait(pids[1], ctx);
	return (ret);
}
