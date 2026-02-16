/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:41:12 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/16 04:13:11 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***STRUCTURES***/

//CMD is for a command, like ls. Everything else is self explainatory
typedef enum	s_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}	t_node_type;

//Type is for the type of redirection, 
//0: <, 1: >, 2: >>, 3: <<
//file points to either a file or a heredoc
typedef struct s_redirect
{
	size_t	type;
	char	*file;
	struct	s_redirect *next;
}	t_redirect;

//This is for NODE_CMD, input[0] is for the cmd
//input[1] and more are for args
typedef struct s_cmd_data
{
	char 		**input;
	t_redirect	*redirects;
}	t_cmd_data;

//We declare t_ast_node here, in order to use it for what's next
typedef struct	s_ast_node	t_ast_node;

//Used for pipe, and, or. Pair left and right token
typedef	struct	s_pair_data
{
	t_ast_node	*left;
	t_ast_node	*right;
}	t_pair_data;

//Used to hold command or pipes, and, or
typedef union	u_node_data
{
	t_cmd_data	cmd;
	t_pair_data	pair;
}	t_node_data;

//Type idenfifies which union member is active
//Data is for what it contains
struct	s_ast_node
{
	t_node_type	type;
	t_node_data	data;
}

//Array of token, nb of them and curr pos in the array
typedef struct s_parser {
    t_token *tokens;
    int token_count;
    int current;
} t_parser;

/***FUNCTIONS***/
//ast_node_helper.c
t_ast_node	*create_cmd_node(char **input, t_redirect *redirects);
t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_ast_node	*create_and_node(t_ast_node *left, t_ast_node *right);
t_ast_node	*create_or_node(t_ast_node *left, t_ast_node *right);
t_redirect	*create_redirect(int type, char *file);

//token_cursor.c
void	init_parser(t_parser *parser, t_token *tokens, int token_count);
t_token	*peek_token(t_parser *parser, int offset);
t_token	*advance(t_parser *parser);
int		match_token(t_parser *parser, t_token_type type, int consume);
int		expect_token(t_parser *parser, t_token_type type, char *error_msg);
