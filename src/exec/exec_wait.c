/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 05:58:53 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 17:09:35 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Wrap waitpid + fetch exit code for either child (if case) or parent
int	exec_wait(pid_t pid, t_ctx *ctx)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		ctx->return_code = 128 + WTERMSIG(status);
		return (ctx->return_code);
	}
	ctx->return_code = WEXITSTATUS(status);
	return (ctx->return_code);
}
