/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:57:04 by amartel           #+#    #+#             */
/*   Updated: 2026/03/22 19:49:51 by jdessoli         ###   ########.fr       */
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

//needed for a dispatch table, maping built-in name to func
typedef struct s_builtin_entry
{
	const char	*name;
	t_builtin_id	id;
	int		(*func)(char **argv, t_ctx *ctx);
}	t_builtin_entry;

//env.c
int		env(t_env *env);

//builtin_utils.c
int		count_args(char **argv);
void	builtin_error(char *builtin, char *arg, char *msg);
int		is_valid_identifier(char *str);
int		is_numeric(char *str);

//env_utils.c
void	set_env_value(t_env **env, char *key, char *value);

//cd_core.c
int		builtin_cd(char **argv);

//pwd_core.c
int		pwd_core(void);

//exit_utils.c
int		parse_exitcode(char *str, int *err_flag);

#endif
