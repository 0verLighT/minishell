/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:57:04 by amartel           #+#    #+#             */
/*   Updated: 2026/04/04 21:01:32 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file builtin.h
 */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "tokenizer.h"
# include <sys/errno.h>

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

/**
 * @brief cd command, change the current directory
 * @param tokens
 * @param token_count
 * @param ctx
 */
int		ft_cd(t_token *tokens, int token_count, t_ctx *ctx);
/**
 * @brief echo command, render argv
 * @param argv
 * @param ctx
 */
int		ft_echo(char **argv, t_ctx *ctx);
/**
 * @brief env command, print shell environement
 * @param env
 */
int		ft_env(t_env *env);
/**
 * @brief exit command, quit minishell
 * @param argv
 * @param ctx
 */
int		ft_exit(char **argv, t_ctx *ctx);
/**
 * @brief export command, add variable in the minishell environement
 * @param argv
 * @param ctx
 */
int		ft_export(char **argv, t_ctx *ctx);
/**
 * @brief pwd command, print working directory
 */
int		ft_pwd(void);
/**
 * @brief unset command, removes a variable from the minishell environment
 * @param argv
 * @param ctx
 */
int		ft_unset(char **argv, t_ctx *ctx);
/**
 * @brief Print environement variable like ft_env ?
 * @param env
 */
void	print_all_export(t_env *env);
/**
 * @brief Check if KEY and KEY=value form are proper export format
 * @param str
 */
int		is_valid_identifier(char *str);
/**
 * @brief get the good exit return code
 * @details In tab, 0 is for i, 1 for j, 2 for err_flag, 3 for sign
 * the modulo is to imitate shell exit code
 * @param str
 * @param err_flag
 */
int		parse_exitcode(char *str, int *err_flag);/**
 * @brief handle no arg hypothesis, call previous functions,
 * set must_free flag to 0 if it was a tilde or dash arg
 * @param tokens
 * @param token_count
 * @param ctx
 * @param must_free
 */
char	*resolve_target(t_token *tokens, int token_count, t_ctx *ctx,
				int *must_free);
/**
 * @brief Updates key=value node, creates the node if needed
 * @param env
 * @param key
 * @param value
 */
int		ft_setenv(t_env **env, const char *key, const char *value);
/**
 * @brief display an builtin error
 * @param builtin
 * @param arg
 * @param msg
 */
void	builtin_error(char *builtin, char *arg, char *msg);
/**
 * @brief Builds a key=value string
 * @param key
 * @param value
 */
char	*build_keyvalue(const char *key, const char *value);

#endif
