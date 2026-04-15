/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:23:27 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/15 05:38:19 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include <stdio.h>

/**
 * @brief Check if a line match the delim
 * @param line
 * @param delim
 */
static int	is_delimiter(char *line, char *delim)
{
	size_t	len;
	size_t	ret;

	len = ft_strlen(delim);
	ret = ft_strncmp(line, delim, len) == 0 && line[len] == '\0';
	return (ret);
}

/**
 * @brief Write a line to the pipe, expands the line if needed
 * (if quoted flag = 0)
 * @param line
 * @param quoted
 * @param ctx
 */
static int	write_line(int fd, char *line, int quoted, t_ctx *ctx)
{
	char	*expanded;
	int		ret;

	if (quoted)
	{
		ret = write(fd, line, ft_strlen(line));
		if (ret < 0)
			return (FAIL);
		return (SUCCESS);
	}
	expanded = ft_expand(line, ctx);
	if (!expanded)
		return (FAIL);
	ret = write(fd, expanded, ft_strlen(expanded));
	if (expanded != line)
		free(expanded);
	if (ret < 0)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief Readline loop until EOF or delim found
 * @param fd
 * @param delim
 * @param quoted
 * @param ctx
 */
static int	fill_heredoc(int fd, char *delim, int quoted, t_ctx *ctx)
{
	char			*line;
	const int		fd_copy = dup(0);

	signal(SIGINT, handle_sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line || g_sig_code == 130)
			break ;
		if (is_delimiter(line, delim))
			break ;
		if (write_line(fd, line, quoted, ctx))
		{
			free(line);
			close(fd);
			close(fd_copy);
			return (FAIL);
		}
		(void) write(fd, "\n", 1);
		free(line);
	}
	post_fill_heredoc(fd_copy, line);
	return (SUCCESS);
}

int	exec_heredoc_pipe(t_redirect *redir, t_ctx *ctx)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	ret = fill_heredoc(fd[1], redir->file, redir->quoted, ctx);
	close(fd[1]);
	if (g_sig_code == 130)
	{
		ctx->return_code = 130;
		close(fd[0]);
		return (FAIL);
	}
	if (ret)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}

int	exec_heredoc(t_redirect *redir, t_ctx *ctx)
{
	int	fd;
	int	fd_copy;

	fd_copy = dup(0);
	fd = exec_heredoc_pipe(redir, ctx);
	if (fd < 0 || g_sig_code == 130)
	{
		dup2(fd_copy, 0);
		close(fd_copy);
		if (fd < 0)
			close(fd);
		return (FAIL);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		dup2(fd_copy, 0);
		close(fd_copy);
		perror("heredoc");
		return (FAIL);
	}
	close(fd);
	return (SUCCESS);
}
