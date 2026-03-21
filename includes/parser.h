/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:41:12 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/21 16:01:30 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "tokenizer.h"

/***STRUCTURES***/

//CMD is for a command, like ls. Everything else is self explainatory
typedef enum s_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}	t_node_type;

typedef enum e_token_type t_token_type;
//token struct, representing each token in a similar fashion
//than my tokenizer, to stay consistent with the logic
typedef struct s_token t_token;

/**
 * @brief Type is for the type of redirection
 * @details 0: <, 1: >, 2: >>, 3: <<
 * file points to either a file or a heredoc
 */
typedef struct s_redirect
{
	size_t				type;
	char				*file;
	struct s_redirect	*next;
}	t_redirect;
/**
 * @brief struct for NODE_CMD
 * @details input[0] is for the command, and input[1] and more is for args
 */
typedef struct s_cmd_data
{
	char		**input;
	t_redirect	*redirects;
}	t_cmd_data;

typedef struct s_ast_node	t_ast_node;

/**
 * @brief Used for pipe, and, or. Pair left and right token
 */
typedef struct s_pair_data
{
	t_ast_node	*left;
	t_ast_node	*right;
}	t_pair_data;

/**
 * @brief Used to hold command or pipes, and, or
 */
typedef union u_node_data
{
	t_cmd_data	cmd;
	t_pair_data	pair;
}	t_node_data;

/**
 * @brief Type idenfifies which union member is active
 * @warning Data is for what it contains
 */
struct	s_ast_node
{
	t_node_type	type;
	t_node_data	data;
};

/**
 * @brief Array of token, nb of them and curr pos in the array
 */
typedef struct s_parser
{
	t_token	*tokens;
	int		token_count;
	int		current;
}	t_parser;

/***FUNCTIONS***/
//ast_node_helper.c

/**
 * @brief Create a command node with its type, args and redir
 * @param input
 * @param redirects
 * @return 
 */
t_ast_node	*create_cmd_node(char **input, t_redirect *redirects);
/**
 * @brief Create a pipe node
 * @param left
 * @param right
 * @return
 */
t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right);
/**
 * @brief Create an AND (type) node
 * @param left
 * @param right
 * @return
 */
t_ast_node	*create_and_node(t_ast_node *left, t_ast_node *right);
/**
 * @brief Create an OR (type) node
 * @param left
 * @param right
 * @return
 */
t_ast_node	*create_or_node(t_ast_node *left, t_ast_node *right);

//clean_up.c
/**
 * @brief 
 */
void		free_string_array(char **array);
void		free_redirects(t_redirect *redirects);
void		free_ast_node(t_ast_node *node);


//token_cursor.c
void		init_parser(t_parser *parser, t_token *tokens, int token_count);
t_token		*peek_token(t_parser *parser, int offset);
t_token		*advance(t_parser *parser);
int			match_token(t_parser *parser, t_token_type type, int consume);
int			expect_token(t_parser *parser, t_token_type type, char *error_msg);

//redirections_utils.c
int			is_redirection(t_token *token);
int			token_to_redir_type(t_token_type type);

//redirection_create.c
t_redirect	*create_redirect(int type, char *file);
void		add_redirection_to_cmd(t_ast_node *cmd_node, t_redirect *new_redir);

//redirection_parse.c
int			parse_redirection(t_parser *parser, t_ast_node *cmd_node);

//pipe_parse.c
t_ast_node	*parse_pipeline(t_parser *parser);

//parse_simple_command.c
int			handle_command_token(t_parser *parser);
void		set_command_context(t_ast_node **cmd_node, char ***input,
				int *argc, int *capacity);

//parse_command_helpers.c
int			handle_redirection_token(t_parser *parser, t_ast_node **cmd_node);
int			handle_word_token(t_parser *parser, char ***input,
				int *argc, int *capacity);
t_ast_node	*finalize_command_node(t_ast_node *cmd_node,
				char **input, int argc);
t_ast_node	*parse_simple_command(t_parser *parser);

//simple_command_utils.c
int			is_command_end(t_token *token);
char		**expand_input_array(char **input, int *capacity);
int			add_word_to_input(char ***input, int *argc,
				int *capacity, char *word);
t_ast_node	*ensure_cmd_node_exists(t_ast_node *cmd_node);
void		cleanup_on_error(t_ast_node *cmd_node, char **input);

#endif
