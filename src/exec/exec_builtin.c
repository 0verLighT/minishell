/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 20:19:50 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/07 20:26:53 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//Handle the builtins base on their enum
static int	run_argv_ctx(t_builtin_id id, char **argv, t_ctx *ctx)
{
	int	ret;

	ret = FAIL;
	if (id == BUILTIN_ECHO)
		ret = ft_echo(argv, ctx);
	else if (id == BUILTIN_CD)
		ret = ft_cd(argv, ctx);
	else if (id == BUILTIN_EXIT)
		ret = ft_exit(argv, ctx);
	else if (id == BUILTIN_EXPORT)
		ret = ft_export(argv, ctx);
	else if (id == BUILTIN_UNSET)
		ret = ft_unset(argv, ctx);
	return (ret);
}

//Needed for builtins who only need the ctx and the env
static int	run_ctx_only(t_builtin_id id, t_ctx *ctx)
{
	int	ret;

	ret = FAIL;
	if (id == BUILTIN_ENV)
		ret = ft_env(ctx->env);
	return (ret);
}

//This func is needed for builtins that don't take args, pwd
static int	run_void(t_builtin_id id)
{
	int	ret;

	ret = FAIL;
	if (id == BUILTIN_PWD)
		ret = ft_pwd();
	return (ret);
}

//Decide what func to call based on the id.
//That way, it assess that pwd needs no args, env need env list
//and the next func, exec_builtin, doesn't have to deal with that
static int	dispatch_builtin(t_builtin_id id, char **argv, t_ctx *ctx)
{
	int	ret;

	if (id == BUILTIN_PWD)
		ret = run_void(id);
	else if (id == BUILTIN_ENV)
		ret = run_ctx_only(id, ctx);
	else
		ret = run_argv_ctx(id, argv, ctx);
	return (ret);
}

//Takes a command name, find what builtin it match, 
//calls the proper function or return fail is there's no match 
int	exec_builtin(char **argv, t_ctx *ctx)
{
	t_builtin_id	id;
	int				ret;

	id = resolve_builtin_id(argv[0]);
	if (id == BUILTIN_NONE)
		return (FAIL);
	ret = dispatch_builtin(id, argv, ctx);
	return (ret);
}
