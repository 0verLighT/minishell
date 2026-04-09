/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 05:58:53 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 05:59:15 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
