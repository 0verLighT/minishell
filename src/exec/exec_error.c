/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 06:05:07 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/10 03:27:41 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_error(char *cmd, char *msg, int exitcode, t_ctx *ctx)
{
	builtin_error(cmd, NULL, msg);
	ctx->return_code = exitcode;
}
