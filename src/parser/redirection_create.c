/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 03:12:06 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/13 16:57:51 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redirect	*create_redirect(int type, char *file)
{
	t_redirect	*redir;

	if (!file)
		return (NULL);
	redir = ft_calloc(sizeof(t_redirect), 1);
	if (!redir)
		return (NULL);
	redir->type = (size_t)type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

/**
 * @brief Points to last redirection in a linked list
 * @details Needed in case of multiple redir
 * @param head
 * @return the last redirect in the param head
 */
static t_redirect	*get_last_redirect(t_redirect *head)
{
	t_redirect	*current;

	if (!head)
		return (NULL);
	current = head;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_redirection_to_cmd(t_ast_node *cmd_node, t_redirect *new_redir)
{
	t_redirect	*last;

	if (!cmd_node || !new_redir || cmd_node->type != NODE_CMD)
		return ;
	if (!cmd_node->data.cmd.redirects)
	{
		cmd_node->data.cmd.redirects = new_redir;
		return ;
	}
	last = get_last_redirect(cmd_node->data.cmd.redirects);
	if (last)
		last->next = new_redir;
}
