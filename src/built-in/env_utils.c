/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:38:08 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/03 17:52:46 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//Mimicking key=value dictionnary logic, key being PATH=, value is /bin
//This function checks if input key match existing key
static int	key_matches(char *var, char *key)
{
	int		i;
	char	*equal;

	equal = ft_strchr(var, '=');
	if (!equal)
		return (0);
	i = 0;
	while (key[i] && &var[i] < equal)
	{
		if (key[i] != var[i])
			return (0);
		i++;
	}
	if (key[i] != '\0' || &var[i] != equal)
		return (0);
	return (1);
}

//Use key_matches to check for a key, and then return a pointer
//to the start of corresponding value, which is after the = sign
char	*get_env_value(t_env *env, char *key)
{
	char	*equal;

	while (env)
	{
		if (key_matches(env->var, key))
		{
			equal = ft_strchr(env->var, '=');
			if (equal)
				return (equal + 1);
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

//Build a node contaning a key + value ensemble, by strlcat both
static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;
	size_t	len;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	len = ft_strlen(key) + ft_strlen(value) + 2;
	new->var = malloc(len);
	if (!new->var)
	{
		free(new);
		return (NULL);
	}
	ft_strlcpy(new->var, key, len);
	ft_strlcat(new->var, "=", len);
	ft_strlcat(new->var, value, len);
	new->next = NULL;
	return (new);
}

//While the function above creates a node, this one is used to modify it
//For exemple to update a USER infos
static int	update_env_var(t_env *env, char *key, char *value)
{
	char	*new_var;
	size_t	len;

	while (env)
	{
		if (key_matches(env->var, key))
		{
			len = ft_strlen(key) + ft_strlen(value) + 2;
			new_var = malloc(len);
			if (!new_var)
				return (0);
			ft_strlcpy(new_var, key, len);
			ft_strlcat(new_var, "=", len);
			ft_strlcat(new_var, value, len);
			free(env->var);
			env->var = new_var;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

//This functions calls the ones above, in this logic:
//Checks args , tries to update existing env var,
//if it doesn't exist creates it instead
void	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!env || !key || !value)
		return ;
	if (update_env_var(*env, key, value))
		return ;
	new = create_env_node(key, value);
	if (!new)
		return ;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
