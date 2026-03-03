/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 09:46:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/14 04:40:08 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_current_dir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("cd");
	return (cwd);
}

static char	*get_home_dir(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		write(2, "cd: HOME not set\n", 17);
	return (home);
}

//todo: update environment variables
static int	handle_cd_no_args(char *home, char *cwd)
{
	if (chdir(home) != 0)
	{
		perror("cd");
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}

//Process cd command based on argument count
static int	cd_process(char **argv, char *home, char *cwd)
{
	int	result;
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		result = handle_cd_no_args(home, cwd);
		return (result);
	}
	if (argc == 2)
	{
		result = handle_cd_with_path(argv[1], cwd);
		return (result);
	}
	ft_putendl_fd("cd: too many arguments", 2);
	free(cwd);
	return (1);
}

//Main cd built-in function
//Takes the command arguments from the AST node
//args[0] = cd, args[1] = path, more args means error
int	builtin_cd(char **argv)
{
	char	*home;
	char	*cwd;
	int		result;

	cwd = get_current_dir();
	if (!cwd)
		return (1);
	home = get_home_dir();
	if (!home)
	{
		free(cwd);
		return (1);
	}
	result = cd_process(argv, home, cwd);
	return (result);
}
