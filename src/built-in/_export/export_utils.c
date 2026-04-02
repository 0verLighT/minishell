/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:53:54 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/02 16:46:37 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Help check for a valid variable name, so alpha or underscore for 1st char
//and alphanum or underscore for the following chars
//_VAR123 is a valid var name, 1VAR isn't
static int	is_valid_identifier_char(char c, int first)
{
	int	is_first_char;
	int	isnt_first_char;

	if (first)
	{
		is_first_char = (ft_isalpha(c) || c == '_');
		return (is_first_char);
	}
	isnt_first_char = (ft_isalnum(c) || c == '_');
	return (isnt_first_char);
}

//Check if KEY and KEY=value form are proper export format
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!is_valid_identifier_char(str[0], 1))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!is_valid_identifier_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

//Search for a value assignment, if there's none it's just a key declaration
//therefore gives the bash-like output
//If there is, isolate the key, print what must be, free key
static void	print_export_entry(const char *var)
{
	const char	*val_assign;
	char		*key;

	val_assign = ft_strchr(var, '=');
	if (!val_assign)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(var, STDOUT_FILENO);
		return ;
	}
	key = ft_substr(var, 0, val_assign - var);
	if (!key)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(eq + 1, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
	free(key);
}

void	print_all_export(t_env *env)
{
	while (env)
	{
		print_export_entry(env->var);
		env = env->next;
	}
}
