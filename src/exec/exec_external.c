/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 01:48:39 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/12 03:54:24 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Built a full path
 * @details Is used to built a full path, joins a dir, /, the cmd name
 * and check if it's executable with access, if it is returns it
 * @param dir
 * @param cmd
 */
static char	*try_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;
	char	*dir_copy;

	dir_copy = strdup(dir);
	tmp = ft_strjoin(dir_copy, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

/**
 * @brief Fetch PATH from env
 * @param cmd
 * @param ctx
 * @return The frist exec found
 */
static char	*search_path(char *cmd, t_ctx *ctx)
{
	char	*path_env;
	char	**dirs;
	char	*full;
	int		i;

	path_env = ft_getenv(ctx->env, "PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	full = NULL;
	while (dirs[i] && !full)
	{
		full = try_path(dirs[i], cmd);
		++i;
	}
	free_array(dirs);
	return (full);
}

/**
 * @brief Distinguish direct and indirect path
 * @details if /, it's a direct path, we can check the executability
 * if there's none, we have to search for the path
 * @param cmd
 * @param ctx
 */
static char	*resolve_path(char *cmd, t_ctx *ctx)
{
	char	*ret;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			ret = ft_strdup(cmd);
			return (ret);
		}
		return (NULL);
	}
	ret = search_path(cmd, ctx);
	return (ret);
}

/**
 * @brief Convert t_env in char **envp for exev
 * @param env
 */
static char	**build_envp(t_env *env)
{
	t_env	*cur;
	char	**envp;
	int		count;
	int		i;

	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	envp = ft_calloc(count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	cur = env;
	while (cur)
	{
		envp[i++] = cur->var;
		cur = cur->next;
	}
	return (envp);
}

int	exec_external(char **argv, t_ctx *ctx)
{
	char	*path;
	char	**envp;
	int		ret;

	path = resolve_path(argv[0], ctx);
	if (!path)
	{
		builtin_error(argv[0], NULL, "command not found");
		return (127);
	}
	envp = build_envp(ctx->env);
	if (!envp)
	{
		free(path);
		return (FAIL);
	}
	ret = execve(path, argv, envp);
	free(path);
	free(envp);
	if (ret < 0)
		builtin_error(argv[0], NULL, strerror(errno));
	return (126);
}
