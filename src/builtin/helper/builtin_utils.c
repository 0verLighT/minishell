/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:21:22 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/14 17:36:18 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin_error(char *builtin, char *arg, char *msg)
{
	ft_dprintf(2, "minishell: %s:", builtin);
	if (arg)
		ft_dprintf(2, "%s:", arg);
	ft_dprintf(2, "%s\n", msg);
}

char	*build_keyvalue(char *key, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

/**
 * @brief Update envirnoment
 * @param env
 * @param key
 * @param key_l
 * @param new_var
 * @return 1 and updates the node if key is found, 0 otherwise 
 */
static int	update_existing(t_env *env, char *key, size_t key_l, char *new_var)
{
	while (env)
	{
		if (ft_strncmp(env->var, key, key_l) == 0 && env->var[key_l] == '=')
		{
			free(env->var);
			env->var = new_var;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/**
 * @brief Allocates a new node and appends it to the list
 * @param env
 * @param new_var
 */
static int	append_new(t_env **env, char *new_var)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
	{
		free(new_var);
		return (1);
	}
	new_node->var = new_var;
	envadd_back(env, new_node);
	return (0);
}

int	ft_setenv(t_env **env, char *key, char *value)
{
	size_t	key_len;
	int		node_append_flag;
	char	*new_var;

	key_len = ft_strlen(key);
	new_var = build_keyvalue(key, value);
	if (!new_var)
		return (1);
	if (update_existing(*env, key, key_len, new_var))
		return (0);
	node_append_flag = append_new(env, new_var);
	return (node_append_flag);
}
