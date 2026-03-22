/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:06:40 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/22 19:40:41 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief check if next token after redir is a valid filename
 * @param file_token
 * @return 0 on error, 1 on succesfully
 */
static int	validate_redir_filename(t_token *file_token)
{
	if (!file_token)
		return (0);
	if (file_token->type != TOKEN_WORD)
		return (0);
	return (1);
}

/**
 * @brief Prints syntax error matching bash's format
 * @details Shows what unexpected token was found after redirection
 * @param file_token
 */
static void	print_redir_error(t_token *file_token)
{
	const char	*line_error = "minishel: syntax error near unexpected token";

	if (!file_token || file_token->type == TOKEN_EOF)
		ft_dprintf(2, "%s 'newline'", line_error);
	else if (file_token->type == TOKEN_PIPE)
		ft_dprintf(2, "%s '|'", line_error);
	else if (file_token->type == TOKEN_LESS)
		ft_dprintf(2, "%s '<'", line_error);
	else if (file_token->type == TOKEN_GREAT)
		ft_dprintf(2, "%s '>'", line_error);
	else if (file_token->type == TOKEN_DLESS)
		ft_dprintf(2, "%s '<<'", line_error);
	else if (file_token->type == TOKEN_DGREAT)
		ft_dprintf(2, "%s '>>'", line_error);
	else
		return ;
}

/**
 * @brief Append a redirection to the command node
 * @param parser
 * @param cmd_node
 * @param redir_type
 * @param file_token
 * @return -1 on error, 0 on succesfully
 */
static int	append_redir(t_parser *parser, t_ast_node *cmd_node,
									int redir_type, t_token *file_token)
{
	t_redirect	*new_redir;

	new_redir = create_redirect(redir_type, file_token->content.ptr);
	if (!new_redir)
		return (-1);
	add_redirection_to_cmd(cmd_node, new_redir);
	advance(parser);
	return (0);
}

int	parse_redirection(t_parser *parser, t_ast_node *cmd_node)
{
	t_token		*redir_token;
	t_token		*file_token;
	int			redir_type;
	int			returned_value;

	redir_token = peek_token(parser, 0);
	if (!redir_token || !is_redirection(redir_token))
		return (-1);
	advance(parser);
	file_token = peek_token(parser, 0);
	if (!validate_redir_filename(file_token))
	{
		print_redir_error(file_token);
		return (-1);
	}
	redir_type = token_to_redir_type(redir_token->type);
	if (redir_type == -1)
		return (-1);
	returned_value = append_redir(parser, cmd_node, redir_type, file_token);
	return (returned_value);
}
