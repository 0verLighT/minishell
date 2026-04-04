/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 09:46:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 19:47:39 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "tokenizer.h"

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
 * @brief wrap resolve_target to return an error
 * if it's a cd had no target situation
 * @details if needed, check cd_helper's last function to better understand
 * @param tokens
 * @param ctx
 * @param target
 * @param tab tab [0] correspond to token_count, tab[1] correspond to must free
 */
static int	get_target(t_token *tokens, t_ctx *ctx, char **target, int *tab)
{
	*target = resolve_target(tokens, tab[0], ctx, &tab[1]);
	if (!*target)
		return (1);
	return (0);
}

/**
 * @brief wrap chdir to both handles errors and free what must be on failure
 * @param target
 * @param old_cwd
 * @param tab
 */
static int	change_dir(char *target, char *old_cwd, int *tab)
{
	if (chdir(target) != 0)
	{
		builtin_error("cd", target, strerror(errno));
		if (tab[1])
			free(target);
		free(old_cwd);
		return (1);
	}
	if (tab[1])
		free(target);
	return (0);
}

int	ft_cd(t_token *tokens, int token_count, t_ctx *ctx)
{
	char	*old_cwd;
	char	*target;
	int		tab[2];
	int		update_flag;

	tab[0] = token_count;
	tab[1] = 0;
	if (get_cwd(&old_cwd))
		return (1);
	if (get_target(tokens, ctx, &target, tab))
	{
		free(old_cwd);
		return (1);
	}
	if (change_dir(target, old_cwd, tab))
		return (1);
	update_flag = update_env(ctx, old_cwd);
	return (update_flag);
}
