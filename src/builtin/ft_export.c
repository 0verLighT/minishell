/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:47:06 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/05 01:08:08 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Take a single arg and update the shell env
 * @param arg
 * @param ctx
 */
static int	export_one(char *arg, t_ctx *ctx)
{
	char	*val_assign;
	char	*key;
	int		setenv_success_check;

	val_assign = ft_strchr(arg, '=');
	if (!val_assign)
		return (SUCCESS);
	key = ft_substr(arg, 0, val_assign - arg);
	if (!key)
		return (FAIL);
	setenv_success_check = ft_setenv(&ctx->env, key, val_assign + 1);
	free(key);
	return (setenv_success_check);
}

/**
 * @brief Validate then export one arg, accumulate worst return code
 * @param arg
 * @param ctx
 */
static int	handle_arg(char *arg, t_ctx *ctx)
{
	int	export_one_check;

	if (!is_valid_identifier(arg))
	{
		builtin_error("export", arg, "not a valid identifier");
		return (FAIL);
	}
	export_one_check = export_one(arg, ctx);
	return (export_one_check);
}

int	ft_export(char **argv, t_ctx *ctx)
{
	int	i;
	int	final_result_code;
	int	tmp;

	if (!argv[1])
	{
		print_all_export(ctx->env);
		return (SUCCESS);
	}
	i = 1;
	while (argv[i])
	{
		tmp = handle_arg(argv[i], ctx);
		if (tmp != SUCCESS)
			final_result_code = tmp;
		++i;
	}
	return (final_result_code);
}
