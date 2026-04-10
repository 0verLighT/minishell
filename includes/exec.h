/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:04:01 by amartel           #+#    #+#             */
/*   Updated: 2026/04/10 03:36:35 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exec.h
 */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "builtin.h"
# include "parser.h"
# include <sys/types.h>

//used to save the fds, so it doesn't get lost with dup2 calls
typedef struct s_fdsave
{
	int	stdin_fd;
	int	stdout_fd;
}	t_fdsave;

typedef struct s_builtin_entry	t_builtin_entry;
typedef struct s_ctx			t_ctx;
typedef struct s_ast_node		t_ast_node;
typedef struct s_redirect		t_redirect;
typedef enum e_builtin_id		t_builtin_id;

//exec_core.c
/**
 * @brief Entry point fo exec call. Call dispatch, then store return code
 * @param node
 * @param ctx
 */
int				exec_node(t_ast_node *node, t_ctx *ctx);
//exec_logical.c
/**
 * @brief dispatcher of the function [exec_or, exec_and]
 * @param node
 * @param ctx
 */
int				exec_logical(t_ast_node *node, t_ctx *ctx);
//exec_cmd.c
/**
 * @brief Check if cmd it's builtin or not to call the right function
 * @param node
 * @param ctx
 */
int				exec_cmd(t_ast_node *node, t_ctx *ctx);
//exec_builtin.c
/**
 * @brief Call the proper function builtin
 * @param argv
 * @param ctx
 */
int				exec_builtin(char **argv, t_ctx *ctx);
//exec_builtin_helper.c
/**
 * @brief Basically a dic with key value pairs, being name and enum
 * @details the NULL serves as a sentinel, just like \0 on a string
 * @param builtins
 */
void			init_builtins(t_builtin_entry *builtins);
/**
 * @brief Check to know if we are looking at a builtin
 * @param name
 */
int				is_builtin(char *name);
/**
 * @brief more evolved version of is_builtin
 * @param name
 * @returns the builtin id
 */
t_builtin_id	resolve_builtin_id(char *name);
//exec_pipe.c
/**
 * @brief Orchestrate, then wait for left then right chidren
 * @return the last children exit code
 */
int				exec_pipe(t_ast_node *node, t_ctx *ctx);
//exec_external.c
/**
 * @brief Orchestrate it all, and return the proper return codes
 * @param argv
 * @param ctx
 */
int				exec_external(char **argv, t_ctx *ctx);
//exec_redir.c
/**
 * @brief Walk the whole redir list, applies each on in order
 * @details If save is non-NULL it means a builtin is running in the parent
 * so it saves the original stdin/stdout via dup before touching anything
 * that's what allows restore_fds in exec_fd.c to undo
 * the redirections afterward.
 * @param redirs
 * @param save
 */
int				apply_redirections(t_redirect *redirs, t_fdsave *save);
//exec_heredoc.c
/**
 * @brief Create the pipe, fills it, redir stdin to read the end
 * @details The write end is closed before the dup2 
 * so the child sees EOF when it drains the pipe
 * @param redir
 * @param ctx
 */
int				exec_heredoc(t_redirect *redir, t_ctx *ctx);
//exec_expand.c
/**
 * @brief Handle expand '$USER'
 * @param str
 * @param ctx
 */
char			*ft_expand(char *str, t_ctx *ctx);
//exec_fd.h
/**
 * @brief Restore fd of strdin and stdout
 * @param save
 */
void			restore_fds(t_fdsave *save);
// exec_wait.c — waitpid and store result in ctx->return_code
/**
 * @brief Wrap waitpid anbd fetch exit code for either child
 * (if case) or parent
 * @param pid
 * @param ctx
 */
int				exec_wait(pid_t pid, t_ctx *ctx);
// exec_error.c — unified error reporting for exec
/**
 * @brief Handle Error in exec
 * @param cmd
 * @param msg
 * @param exitcode
 * @param ctx
 */
void			exec_error(char *cmd, char *msg, int exitcode, t_ctx *ctx);

#endif
