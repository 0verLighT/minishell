/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:08:27 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/14 00:50:25 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Handles '<'
 * @param file
 */
static int	redir_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		builtin_error(file, NULL, strerror(errno));
		return (FAIL);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		builtin_error(file, NULL, strerror(errno));
		return (FAIL);
	}
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Handles '>'and '>>'
 * @details O_TRUNC for '>', O_APPEND for '>>'
 * open 0644 because it's the standart file permission
 * @param file
 * @param append
 */
static int	redir_output(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		builtin_error(file, NULL, strerror(errno));
		return (FAIL);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		builtin_error(file, NULL, strerror(errno));
		return (FAIL);
	}
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Dispatch the redirect node according to it's type
 * @param redir
 */
static int	apply_one(t_redirect *redir, t_ctx *ctx)
{
	if (redir->type == 0)
		return (redir_input(redir->file));
	if (redir->type == 1)
		return (redir_output(redir->file, 0));
	if (redir->type == 2)
		return (redir_output(redir->file, 1));
	if (redir->type == 3)
		return (exec_heredoc(redir, ctx));
	return (FAIL);
}

int	apply_redirections(t_redirect *redirs, t_fdsave *save, t_ctx *ctx)
{
	if (save)
	{
		save->stdin_fd = dup(STDIN_FILENO);
		save->stdout_fd = dup(STDOUT_FILENO);
	}
	while (redirs)
	{
		if (apply_one(redirs, ctx))
		{
			if (save)
				restore_fds(save);
			return (FAIL);
		}
		redirs = redirs->next;
	}
	return (SUCCESS);
}
