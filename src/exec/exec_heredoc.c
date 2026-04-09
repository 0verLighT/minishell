/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 20:23:27 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 17:09:43 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Check if a line match the delim
static int	is_delimiter(const char *line, const char *delim)
{
	size_t	len;
	size_t	ret;

	len = ft_strlen(delim);
	ret = ft_strncmp(line, delim, len) == 0 && line[len] == '\n';
	return (ret);
}

//Write a line to the pipe, expands the line if needed (if quoted flag = 0)
static int	write_line(int fd, const char *line, int quoted, t_ctx *ctx)
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
	free(expanded);
	if (ret < 0)
		return (FAIL);
	return (SUCCESS);
}

//Readline loop until EOF or delim found
static int	fill_heredoc(int fd, const char *delim, int quoted, t_ctx *ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(line, delim))
		{
			free(line);
			break ;
		}
		if (write_line(fd, line, quoted, ctx))
		{
			free(line);
			return (FAIL);
		}
		write(fd, "\n", 1);
		free(line);
	}
	return (SUCCESS);
}

//Create the pipe, fills it, redir stdin to read the end
//The write end is closed before the dup2 
//so the child sees EOF when it drains the pipe
int	exec_heredoc(t_redirect *redir, t_ctx *ctx)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (FAIL);
	}
	ret = fill_heredoc(fd[1], redir->file, redir->quoted, ctx);
	close(fd[1]);
	if (ret)
	{
		close(fd[0]);
		return (FAIL);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		close(fd[0]);
		perror("heredoc");
		return (FAIL);
	}
	close(fd[0]);
	return (SUCCESS);
}
