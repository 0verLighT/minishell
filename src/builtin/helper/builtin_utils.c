/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:21:22 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 21:00:18 by amartel          ###   ########.fr       */
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

char	*build_keyvalue(const char *key, const char *value)
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
 * @param node
 * @param key
 * @param key_len
 * @param new_var
 * @return 1 and updates the node if key is found, 0 otherwise 
 */
static int	update_existing(t_env *node, const char *key,
		size_t key_len, char *new_var)
{
	while (node)
	{
		if (ft_strncmp(node->var, key, key_len) == 0
			&& node->var[key_len] == '=')
		{
			free(node->var);
			node->var = new_var;
			return (1);
		}
		node = node->next;
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

int	ft_setenv(t_env **env, const char *key, const char *value)
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
