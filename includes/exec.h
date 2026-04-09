/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:04:01 by amartel           #+#    #+#             */
/*   Updated: 2026/04/07 03:58:28 by amartel          ###   ########.fr       */
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

//used to save the fds, so it doesn't get lost with dup2 calls
typedef struct s_fdsave
{
	int	stdin_fd;
	int	stdout_fd;
}	t_fdsave;

typedef struct s_builtin_entry	t_builtin_entry;
typedef struct s_ctx			t_ctx;
typedef struct s_ast_node		t_ast_node;
typedef enum e_builtin_id		t_builtin_id;

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
//exec_pipe.c
int				exec_pipe(t_ast_node *node, t_ctx *ctx);
//exec_external.c
int				exec_external(char **argv, t_ctx *ctx);
//exec_redir.c
int				apply_redirections(t_redirect *redirs, t_fdsave *save);
//exec_heredoc.c
int				exec_heredoc(t_redirect *redir, t_ctx *ctx);
//exec_expand.c
char			*ft_expand(const char *str, t_ctx *ctx);
//exec_fd.h
void			restore_fds(t_fdsave *save);
// exec_wait.c — waitpid and store result in ctx->return_code
int				exec_wait(pid_t pid, t_ctx *ctx);
// exec_error.c — unified error reporting for exec
void			exec_error(const char *cmd, const char *msg,
					int exitcode, t_ctx *ctx);

#endif
