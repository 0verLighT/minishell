/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 01:19:51 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/22 17:14:10 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
}

/**
 * @brief Free the data in a command node
 * @param node the AST
 */
static void	free_cmd_node(t_ast_node *node)
{
	free_string_array(node->data.cmd.input);
	free_redirects(node->data.cmd.redirects);
}

/**
 * @brief Free a pipe, and, or node
 * @param node the AST
 */
static void	free_binary_node(t_ast_node *node)
{
	free_ast_node(node->data.pair.left);
	free_ast_node(node->data.pair.right);
}

void	free_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
		free_cmd_node(node);
	else
		free_binary_node(node);
	free(node);
}
