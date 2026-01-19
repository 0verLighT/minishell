/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 06:09:07 by amartel           #+#    #+#             */
/*   Updated: 2026/01/19 03:57:20 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	tmp = envlast(tmp);
	tmp->next = new;
}

static	t_env *new_node_env(char *env)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var = env;
	return (new_node);
}

static t_env	*init_env(char **envp)
{
	t_env	*env;
	size_t	i;
	t_env	*temp;

	i = 0;
	env = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		temp = new_node_env(envp[i++]);
		envadd_back(&env, temp);
	}
	return (env);
}

t_ctx	*init_ctx(t_ctx *ctx, char **envp)
{
	
	ctx->env = init_env(envp);
	return(ctx);
}
