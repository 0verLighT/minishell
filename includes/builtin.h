/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:57:04 by amartel           #+#    #+#             */
/*   Updated: 2026/02/20 19:19:14 by amartel          ###   ########.fr       */
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

#endif
