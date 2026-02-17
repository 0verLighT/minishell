/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 02:19:44 by amartel           #+#    #+#             */
/*   Updated: 2026/02/17 04:34:11 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->var);
		free(tmp);
	}
	env = NULL;
}

void	free_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	free_env(ctx->env);
	free(ctx->prompt);
	free(ctx);
}
