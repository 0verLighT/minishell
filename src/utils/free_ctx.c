/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:15:04 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/23 17:15:54 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->var);
		free(env);
		env = next;
	}
}

void	free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	free_env(ctx->env);
	free(ctx->prompt);
	ctx->env = NULL;
	ctx->prompt = NULL;
}
