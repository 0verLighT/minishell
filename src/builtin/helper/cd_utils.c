/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:45:53 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 20:56:03 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief fetch $HOME from env
 * @param ctx
 */
static char	*resolve_home(t_ctx *ctx)
{
	char	*target;

	target = ft_getenv(ctx->env, "HOME");
	if (!target)
		builtin_error("cd", NULL, "HOME not set");
	return (target);
}

/**
 * @brief fetch $OLDPWD and print it
 * @param ctx
 */
static char	*resolve_oldpwd(t_ctx *ctx)
{
	char	*target;

	target = ft_getenv(ctx->env, "OLDPWD");
	if (!target)
	{
		builtin_error("cd", NULL, "OLDPWD not set");
		return (NULL);
	}
	ft_dprintf(1, "%s\n", target);
	return (target);
}

/**
 * @brief Fetch the arg for cd and activate a must_free flag
 * @param tokens
 * @param must_free
 */
static char	*resolve_arg(t_token *tokens, int *must_free)
{
	char	*arg;

	arg = ft_substr(tokens[1].content.ptr, 0, tokens[1].content.len);
	if (!arg)
		return (NULL);
	*must_free = 1;
	return (arg);
}

/**
 * @brief Handle ~ and - arg for cd 
 * @param arg
 * @param ctx
 */
static char	*resolve_tilde_or_dash(char *arg, t_ctx *ctx)
{
	if (ft_strcmp(arg, "~") == 0)
	{
		free(arg);
		return (resolve_home(ctx));
	}
	if (ft_strcmp(arg, "-") == 0)
	{
		free(arg);
		return (resolve_oldpwd(ctx));
	}
	return (arg);
}

char	*resolve_target(t_token *tokens, int token_count, t_ctx *ctx,
				int *must_free)
{
	char	*arg;
	char	*target;

	*must_free = 0;
	if (token_count == 1)
	{
		arg = resolve_home(ctx);
		return (arg);
	}
	arg = resolve_arg(tokens, must_free);
	if (!arg)
		return (NULL);
	target = resolve_tilde_or_dash(arg, ctx);
	if (target != arg)
		*must_free = 0;
	return (target);
}
