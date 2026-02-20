/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 02:33:26 by amartel           #+#    #+#             */
/*   Updated: 2026/02/20 19:15:34 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minishell.h
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "builtin.h"
# include "signals.h"

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
	t_env	*env;
	char	*prompt;
	int		return_code;
}	t_ctx;

t_ctx	*init_ctx(t_ctx *ctx, char **envp);

#endif
