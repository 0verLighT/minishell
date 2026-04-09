/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 06:05:07 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 06:05:28 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_error(const char *cmd, const char *msg, int exitcode, t_ctx *ctx)
{
	builtin_error(cmd, NULL, msg);
	ctx->return_code = exitcode;
}
