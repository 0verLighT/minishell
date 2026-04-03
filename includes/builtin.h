/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:57:04 by amartel           #+#    #+#             */
/*   Updated: 2026/04/02 21:42:03 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin.h
 */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_env	t_env;

# ifndef SUCCESS
#  define SUCCESS 0
# endif
# ifndef FAIL
#  define FAIL 1
# endif

//needed for dispatching the built-ins
typedef enum e_builtin_id
{
	BUILTIN_NONE = 0,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXIT,
	BUILTIN_ENV,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_HISTORY,
}	t_builtin_id;

//neede for a dispatch table, maping built-in name to func
typedef struct s_builtin_entry
{
	const char	*name;
	t_builtin_id	id;
	int		(*func)(char **argv, t_ctx *ctx);
}	t_builtin_entry;

//env.c
int		env(t_env *env);

//builtin_utils.c
void	builtin_error(char *builtin, char *arg, char *msg);
char	*build_keyvalue(const char *key, const char *value);
int		ft_setenv(t_env **env, const char *key, const char *value);

//_cd/cd_core.c
int	cd_core(t_token *tokens, int token_count, t_ctx *ctx)
//_cd/cd_helper.c
char	*resolve_target(t_token *tokens, int token_count, t_ctx *ctx,
				int *must_free);

//_pwd/pwd_core.c
int		pwd_core(void);

//_exit/exit_utils.c
int		parse_exitcode(char *str, int *err_flag);
//_exit/exit_core.c
int		exit_core(char **argv, t_ctx *ctx);

//_export/export_utils.c
int	is_valid_identifier(const char *str);
void	print_all_export(t_env *env);
//_export/export_core.c
int	export_core(char **argv, t_ctx *ctx);

//_unset/unset_core.c
int	unset_core(char **argv, t_ctx *ctx);

//_echo/echo_core.c
int	echo_core(char **argv, t_ctx *ctx);

#endif
