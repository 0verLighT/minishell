/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 01:19:51 by jdessoli          #+#    #+#             */
/*   Updated: 2026/04/11 03:17:32 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
	array = NULL;
}

void	free_redirects(t_redirect *redirects)
{
	t_redirect	*tmp;

	while (redirects)
	{
		tmp = redirects;
		redirects = redirects->next;
		free(tmp->file);
		free(tmp);
	}
	redirects = NULL;
}

void	free_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		free_array(node->data.cmd.input);
		free_redirects(node->data.cmd.redirects);
	}
	else
	{
		free_ast_node(node->data.pair.left);
		free_ast_node(node->data.pair.right);
	}
	free(node);
	node = NULL;
}
