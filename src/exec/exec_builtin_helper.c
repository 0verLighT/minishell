/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 21:02:09 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/04 21:03:29 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Basically a dic with key value pairs, being name and enum
//the NULL serves as a sentinel, just like \0 on a string
void	init_builtins(t_builtin_entry *builtins)
{
	builtins[0] = (t_builtin_entry){"echo", BUILTIN_ECHO, NULL};
	builtins[1] = (t_builtin_entry){"cd", BUILTIN_CD, NULL};
	builtins[2] = (t_builtin_entry){"pwd", BUILTIN_PWD, NULL};
	builtins[3] = (t_builtin_entry){"exit", BUILTIN_EXIT, NULL};
	builtins[4] = (t_builtin_entry){"env", BUILTIN_ENV, NULL};
	builtins[5] = (t_builtin_entry){"export", BUILTIN_EXPORT, NULL};
	builtins[6] = (t_builtin_entry){"unset", BUILTIN_UNSET, NULL};
	builtins[7] = (t_builtin_entry){NULL, BUILTIN_NONE, NULL};
}

//parse the table above, to know what builtin to pick
static t_builtin_id	get_builtin_id(const char *name,
						t_builtin_entry *builtins)
{
	int	i;

	i = 0;
	while (builtins[i].name)
	{
		if (ft_strcmp(builtins[i].name, name) == 0)
			return (builtins[i].id);
		i++;
	}
	return (BUILTIN_NONE);
}

//check to know if we are looking at a builtin
//which is needed to know if we need to fork
int	is_builtin(const char *name)
{
	t_builtin_entry	builtins[8];
	t_builtin_id	id;

	init_builtins(builtins);
	id = get_builtin_id(name, builtins);
	return (id != BUILTIN_NONE);
}

//more evolved version of the one above, returns the builtin id
t_builtin_id	resolve_builtin_id(const char *name)
{
	t_builtin_entry	builtins[8];
	t_builtin_id	id;

	init_builtins(builtins);
	id = get_builtin_id(name, builtins);
	return (id);
}
