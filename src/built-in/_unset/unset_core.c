/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:15:07 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/02 21:42:43 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Helper function for the next one, check if the key of the node
//match the key in env list
static int	is_matching_key(const char *var, const char *key, size_t key_len)
{

	int key_check;

	if (ft_strncmp(var, key, key_len) == 0
		&& (var[key_len] == '=' || var[key_len] == '\0'))
		key_check = 1;
	else
		key_check = 0;
	return (key_check);
}

//Remove the node matching key from the env list
static void	remove_env_node(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;
	size_t	key_len;

	key_len = ft_strlen(key);
	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (is_matching_key(cur->var, key, key_len))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->var);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

//The next two functions have the same logic than export_core, 
//so check export_core.c if needed
static int	unset_one(char *arg, t_ctx *ctx)
{
	if (!is_valid_identifier(arg))
	{
		builtin_error("unset", arg, "not a valid identifier");
		return (FAIL);
	}
	remove_env_node(&ctx->env, arg);
	return (SUCCESS);
}

int	unset_core(char **argv, t_ctx *ctx)
{
	int	i;
	int	final_result_code;
	int	tmp;

	if (!argv[1])
		return (SUCCESS);
	i = 1;
	final_result_code = SUCCESS;
	while (argv[i])
	{
		tmp = unset_one(argv[i], ctx);
		if (tmp != SUCCESS)
			final_result_code = tmp;
		i++;
	}
	return (final_result_code);
}
