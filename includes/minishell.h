/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:33:26 by amartel           #+#    #+#             */
/*   Updated: 2026/04/07 03:54:58 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minishell.h
 */

#ifndef MINISHELL_H
# define MINISHELL_H

//.h of the different minishell parts
# include "builtin.h"
# include "exec.h"
# include "parser.h"
# include "signals.h"
# include "tokenizer.h"
# include "utils.h"
//lib needed for the whole project
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# ifndef HOST_NAME_MAX
#  ifdef __APPLE__
#   define HOST_NAME_MAX 255
#  else
#   define HOST_NAME_MAX 64
#  endif
# endif

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_ctx
{
	char	*prompt;
	int		return_code;
	t_env	*env;
}	t_ctx;

/**
 * @brief Initialization of the context structure
 * @param ctx A pointer to the ctx variable to be initialize
 * @param envp The environement variable in array
 * @return A pointer to the initialize context
 */
t_ctx	*init_ctx(t_ctx *ctx, char **envp);
/**
 * @brief Adds a new element at the end of the environment linked list
 * @param env A pointer to the head of the envirnoment list
 * @param new The new element to be added
 */
void	envadd_back(t_env **env, t_env *new);

#endif
