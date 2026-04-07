/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 19:08:27 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/07 19:08:43 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Handles <
static int	redir_input(const char *file)
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

//Handles > and >>
//O_TRUNC for >, O_APPEND for >>
//open 0644 because it's the standart file permission
static int	redir_output(const char *file, int append)
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

//Dispatch the redirect node according to it's type
static int	apply_one(t_redirect *redir)
{
	if (redir->type == 0)
		return (redir_input(redir->file));
	if (redir->type == 1)
		return (redir_output(redir->file, 0));
	if (redir->type == 2)
		return (redir_output(redir->file, 1));
	return (FAIL);
}

//Walk the whole redir list, applies each on in order
//If save is non-NULL it means a builtin is running in the parent
//so it saves the original stdin/stdout via dup before touching anything
//that's what allows restore_fds in exec_fd.c to undo the redirections afterward. 
int	apply_redirections(t_redirect *redirs, t_fdsave *save)
{
	if (save)
	{
		save->stdin_fd = dup(STDIN_FILENO);
		save->stdout_fd = dup(STDOUT_FILENO);
	}
	while (redirs)
	{
		if (apply_one(redirs))
		{
			if (save)
				restore_fds(save);
			return (FAIL);
		}
		redirs = redirs->next;
	}
	return (SUCCESS);
}
