/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:09:07 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/07 00:48:21 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
/**
 * @brief
 * @param exitcode
 * @param ctx
 */
static int	handle_exit(int exitcode, t_ctx *ctx)
{
	exitcode = ctx->return_code;
	free_ctx(ctx);
	return (exitcode);
}

int	ft_exit(char **argv, t_ctx *ctx)
{
	int	err_flag;
	int	exitcode;

	exitcode = 0;
	ft_dprintf(1, "exit");
	if (!argv[1])
	{
		exitcode = handle_exit(exitcode, ctx);
		exit(exitcode);
	}
	if (argv[2])
	{
		builtin_error("exit", NULL, "too many arguments");
		return (1);
	}
	err_flag = 0;
	exitcode = parse_exitcode(argv[1], &err_flag);
	if (err_flag)
	{
		builtin_error("exit", argv[1], "numeric argument required");
		free_ctx(ctx);
		exit(2);
	}
	free_ctx(ctx);
	exit(exitcode);
}
