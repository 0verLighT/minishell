/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 02:19:44 by amartel           #+#    #+#             */
/*   Updated: 2026/04/18 05:00:21 by amartel          ###   ########.fr       */
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
	if (ctx->tokens)
	{
		free_tokens(ctx->tokens, ctx->nb_token);
		ctx->tokens = NULL;
	}
	free(ctx);
}

void	free_in_run_child(t_ast_node *node, t_ctx *ctx)
{
	free_ast_node(node);
	free_tokens(ctx->tokens, ctx->nb_token);
	ctx->tokens = NULL;
	free_ctx(ctx);
}
