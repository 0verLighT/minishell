/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 02:59:28 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/17 03:11:38 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Checks if a token represents a redirection operator
int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_LESS)
		return (1);
	if (token->type == TOKEN_GREAT)
		return (1);
	if (token->type == TOKEN_DLESS)
		return (1);
	if (token->type == TOKEN_DGREAT)
		return (1);
	return (0);
}

//Converts token type to redirection type for the .h struct
size_t	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_LESS)
		return (0);
	if (type == TOKEN_GREAT)
		return (1);
	if (type == TOKEN_DGREAT)
		return (2);
	if (type == TOKEN_DLESS)
		return (3);
	return (-1);
}
