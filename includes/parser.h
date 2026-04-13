/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:41:12 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/13 02:12:46 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parser.h
 */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "tokenizer.h"
# include <stdio.h>

//CMD is for a command, like ls. Everything else is self explainatory
typedef enum s_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}	t_node_type;

typedef enum e_token_type	t_token_type;
//token struct, representing each token in a similar fashion
//than my tokenizer, to stay consistent with the logic
typedef struct s_token		t_token;

/**
 * @brief Type is for the type of redirection
 * @details 0: <, 1: >, 2: >>, 3: <<
 * file points to either a file or a heredoc
 * the int quoted is a flag to mark when a delimiter was found quoted
 */
typedef struct s_redirect
{
	char				*file;
	size_t				type;
	int					quoted;
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

/**
 * @brief 
 */
typedef struct s_cmd_ctx
{
	t_ast_node	*cmd_node;
	char		**input;
	int			argc;
	int			capacity;
}	t_cmd_ctx;

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
 * @brief Like free split
 * @param array
 */
void		free_array(char **array);
/**
 * @brief Free a linked list of redir
 * @param redirects
 */
void		free_redirects(t_redirect *redirects);
/**
 * @brief Free the entire AST
 * @param node the AST
 */
void		free_ast_node(t_ast_node *node);

//parse_command_helpers.c
/**
 * @brief Check if there's a redir token. add it
 * @param parser 
 * @param cmd_node 
 * @return -1 on error, 1 on successfully
 */
int			handle_redirection_token(t_parser *parser, t_cmd_ctx *ctx);
/**
 * @brief Same as above but for words
 * @param parser
 * @param input
 * @return -1 on error, 1 on successfully
 */
int			handle_word_token(t_parser *parser, t_cmd_ctx *ctx);
/**
 * @brief Gives the input to the cmd_node, finalizing it for exec use
 * @param ctx
 * @param parser
 * @return AST node
 */
t_ast_node	*finalize_command_node(t_cmd_ctx *ctx, t_parser *parser);
/**
 * @brief Parses a simple command with args and redirections
 * @param parser
 * @details 10 capacity is an arbitrary choice, realistic number of args for a
 * word, If needed will be doubled (see simple_command_utils.c)
 * counters[0] is for argc, [1] is for capacity
 * @return Parser command in the AST node
 */
t_ast_node	*parse_simple_command(t_parser *parser);

//parse_simple_command.c

/**
 * @brief Check the type of token and call the according function
 * @param parser
 * @param ctx
 * @return -1 on error, 0 on succesfully
 */
int			handle_command_token(t_parser *parser, t_cmd_ctx *ctx);

//pipe_parse.c
/**
 * @brief Parses an input with multiple pipes
 * @return Root of pipeline tree
 */
t_ast_node	*parse_pipeline(t_parser *parser);

//redirection_create.c
/**
 * @brief Init a redirection node
 * @param type
 * @param file
 * @return New redirection
 */
t_redirect	*create_redirect(int type, char *file);
/**
 * @brief Appends a redirection to the end of command's redirection list
 * @details While preservesing order of redirections
 * @param cmd_node
 * @param new_redir
 */
void		add_redirection_to_cmd(t_ast_node *cmd_node, t_redirect *new_redir);

//redirection_parse.c

/**
 * @brief Parses a single redir (operator + filename)
 * @details Get cursor beyond them if success
 * @param parser
 * @param cmd_node
 * @return -1 on error
 */
int			parse_redirection(t_parser *parser, t_ast_node *cmd_node);

//redirections_utils.c
/**
 * @brief Checks if a token represents a redirection operator
 * @param token
 * @return 0 on error, 1 on succesfully
 */
int			is_redirection(t_token *token);
/**
 * @brief Converts token type to redirection type for the .h struct
 * @return The number type of token
 */
int			token_to_redir_type(t_token_type type);

//simple_command_utils.c
/**
 * @brief Checks if token is a binary operator or EOF
 * @details to know if another cmd is next
 * @param token
 * @return 1 on error, 0 on sucessfully
 */
int			is_command_end(t_token *token);
/**
 * @brief Double the capacity of the array
 * @param ctx
 * @return the new array
 */
char		**expand_input_array(t_cmd_ctx *ctx);
/**
 * @brief Adds a word token to the input array, if needed expanded
 * @param ctx
 * @param word
 * @return -1 on error, 0 on successfully
 */
int			add_word_to_input(t_cmd_ctx *ctx, char *word);
/**
 * @brief Initializes a command node if not yet created
 * @details Needed in case a redirection appears first in input
 * @param cmd_node
 * @return New node of ast
 */
t_ast_node	*ensure_cmd_node_exists(t_ast_node *cmd_node);
/**
 * @brief Free if error occues during command parsing
 * @param ctx
 */
void		free_cmd_ctx(t_cmd_ctx *ctx);

//token_cursor.c
/**
 * @brief Initialize the parser with tokens
 * @param parser
 * @param tokens
 * @param token_count
 */
void		init_parser(t_parser *parser, t_token *tokens, int token_count);
/**
 * @brief Peek at a token offset index
 * @param parser
 * @param offset
 * @return Token with offset
 */
t_token		*peek_token(t_parser *parser, int offset);
/**
 * @brief Consume current token and move to next
 * @param parser
 * @param type
 * @param consune
 * @return The consumed token
 */
t_token		*advance(t_parser *parser);
/**
 * @brief Allows to either check if the token match a type 
 * and then either peek or consume it
 * @param parser
 * @param type
 * @param consume
 * @return 0 on error, 1 on succesfully
 */
int			match_token(t_parser *parser, t_token_type type, int consume);
/**
 * @brief Expect a specific token type, consume it or report error
 * @param parser
 * @param type
 * @param error_msg
 * @return 0 on error, 1 on succesfully and cusume the token
 */
int			expect_token(t_parser *parser, t_token_type type, char *err_msg);
/**
 * @brief Prints syntax error matching bash's format
 * @details Shows what unexpected token was found after redirection
 * @param file_token
 */
void		print_redir_error(t_token *file_token);
/**
 * @brief Build the command struture
 * @param paser
 * @param ctx context of command
 * @return -1 on error, 0 on successfully
 */
int			process_command_tokens(t_parser *parser, t_cmd_ctx *ctx);
#endif
