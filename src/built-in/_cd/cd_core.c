/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 09:46:31 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/01 10:44:35 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	handle_cd_no_args(char *home, char *cwd)
{
	if (chdir(home) != 0)
	{
		perror("cd");
		free(cwd);
		return (1);
	}
	//todo: update environment variables
	free(cwd);
	return (0);
}

static int	cd_process(t_token *tokens, int token_count, char *home, char *cwd)
{
	int	result;

	if (token_count == 1)
	{
		result = handle_cd_no_args(home, cwd);
		return (result);
	}
	//todo: add if token_count == 2 here, for if a path is given
	//that's where the token array will be used
	free(cwd);
	return (1);
}

int	cd_core(t_token *tokens, int token_count)
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
	result = cd_process(tokens, token_count, home, cwd);
	return (result);
}
