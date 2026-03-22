/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 02:59:28 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/22 19:16:23 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	token_to_redir_type(t_token_type type)
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
