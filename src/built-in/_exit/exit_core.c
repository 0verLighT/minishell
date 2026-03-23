/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:09:07 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/22 19:09:31 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit(int exicode, t_ctx *ctx)
{
	exitcode = ctx->return_code;
	free_ctx(ctx);
	return (exitcode);
}

int	exit_core(char **argv, t_ctx *ctx)
{
	int	err_flag;
	int	exitcode;

	ft_putendl_fd("exit", STDOUT_FILENO);
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
