/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:04:01 by amartel           #+#    #+#             */
/*   Updated: 2026/02/07 18:31:33 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec.h
 */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

//used to save the fds, so it doesn't get lost with dup2 calls
typedef struct s_fdsave
{
    int    stdin_fd;
    int    stdout_fd;
}    t_fdsave;

//exec_core.c
int				exec_node(t_ast_node *node, t_ctx *ctx);
//exec_logical.c
int				exec_logical(t_ast_node *node, t_ctx *ctx);
//exec_cmd.c
int				exec_cmd(t_ast_node *node, t_ctx *ctx);
//exec_builtin.c
int				exec_builtin(char **argv, t_ctx *ctx);
//exec_builtin_helper.c
void			init_builtins(t_builtin_entry *builtins);
int				is_builtin(const char *name);
t_builtin_id	resolve_builtin_id(const char *name);

#endif
