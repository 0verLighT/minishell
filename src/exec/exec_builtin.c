/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 20:19:50 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/07 03:33:38 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//! link -> change builtin name function and ft_cd arg
//Handle the builtins base on their enum
static int	run_argv_ctx(t_builtin_id id, char **argv, t_ctx *ctx)
{
	int	ret;

	ret = FAIL;
	if (id == BUILTIN_ECHO)
		ret = echo_core(argv, ctx);
	else if (id == BUILTIN_CD)
		ret = cd_core(argv, ctx);
	else if (id == BUILTIN_EXIT)
		ret = exit_core(argv, ctx);
	else if (id == BUILTIN_EXPORT)
		ret = export_core(argv, ctx);
	else if (id == BUILTIN_UNSET)
		ret = unset_core(argv, ctx);
	return (ret);
}

//Needed for builtins who only need the ctx and the env
static int	run_ctx_only(t_builtin_id id, t_ctx *ctx)
{
	int	ret;

	ret = FAIL;
	if (id == BUILTIN_ENV)
		ret = env(ctx->env);
	return (ret);
}

//This func is needed for builtins that don't take args, pwd
static int	run_void(t_builtin_id id)
{
	int	ret;

	ret = FAIL;
	if (id == BUILTIN_PWD)
		ret = pwd_core();
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
