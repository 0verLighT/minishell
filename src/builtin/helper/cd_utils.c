/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:45:53 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/09 19:40:33 by amartel          ###   ########.fr       */
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

char	*resolve_target(char **argv, t_ctx *ctx)
{
	if (!argv[1] || argv[1][0] == '~')
		return (resolve_home(ctx));
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
		return (resolve_oldpwd(ctx));
	return (argv[1]);
}
