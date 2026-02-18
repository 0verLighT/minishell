/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 01:19:51 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/18 03:04:59 by jdessoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//Like free Split
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

//Used to free a linked list of redir
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

//Used to free the data in a command node
static void	free_cmd_node(t_ast_node *node)
{
	free_string_array(node->data.cmd.input);
	free_redirects(node->data.cmd.redirects);
}

//Used to free a pipe, and, or node
static void	free_binary_node(t_ast_node *node)
{
	free_ast_node(node->data.pair.left);
	free_ast_node(node->data.pair.right);
}

//Used to free the entire AST
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
