/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:45:30 by amartel           #+#    #+#             */
/*   Updated: 2026/04/09 19:45:31 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief after a cd, save old PWD, set cwd (current working directory)
 * as the new PWD
 * @details if unclear, check builtin_utils.c
 * @param ctx
 * @param old_cwd
 */
static int	update_env(t_ctx *ctx, char *old_cwd)
{
	char	*new_cwd;
	int		ret;

	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		free(old_cwd);
		perror("cd");
		return (1);
	}
	ret = ft_setenv(&ctx->env, "OLDPWD", old_cwd);
	if (!ret)
		ret = ft_setenv(&ctx->env, "PWD", new_cwd);
	free(old_cwd);
	free(new_cwd);
	return (ret);
}

/**
 * @brief wrap getcwd with error management
 * @param old_cwd
 */
static int	get_cwd(char **old_cwd)
{
	*old_cwd = getcwd(NULL, 0);
	if (!*old_cwd)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

/**
 * @brief wrap chdir to both handles errors and free what must be on failure
 * @param target
 * @param old_cwd
 * @param tab
 */
static int	change_dir(char *target, char *old_cwd)
{
	if (chdir(target) != 0)
	{
		builtin_error("cd", target, strerror(errno));
		free(old_cwd);
		return (1);
	}
	return (0);
}

int	ft_cd(char **argv, t_ctx *ctx)
{
	char	*old_cwd;
	char	*target;
	int		update_flag;

	if (get_cwd(&old_cwd))
		return (1);
	target = resolve_target(argv, ctx);
	if (!target)
	{
		free(old_cwd);
		return (1);
	}
	if (change_dir(target, old_cwd))
		return (1);
	update_flag = update_env(ctx, old_cwd);
	return (update_flag);
}
