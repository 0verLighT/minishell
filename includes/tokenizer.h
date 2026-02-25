/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 02:31:28 by jdessoli          #+#    #+#             */
/*   Updated: 2026/02/25 15:47:55 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer.h
 */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include <stdlib.h>

/**
 * @brief Allows to take chunks of the input, with a precise starting and ending 
 * point
 * @param ptr TODO
 * @param len TODO
 */
typedef struct s_slice
{
	char	*ptr;
	size_t	len;
}	t_slice;

/**
 * @brief A token is a chunk of the input with an index That way, we can  
 * work on isolated chunks by giving the index
 * @param index TODO
 * @param content TODO
*/
typedef struct s_token
{
	size_t	index;
	t_slice	content;
}	t_token;

//tokenizer.c
size_t	strskip(char *str, char *charset);
size_t	count_token(char *str);
t_slice	*token_maker(char *str);
void	free_tokens(t_token *tokens);

//tokenizer_utils.c
size_t	get_token_len(char *str, int pos);
int		fill_token(t_token *token, char *str, int pos, int index);
size_t	process_tokens(t_token *tokens, char *str, size_t token_count);
t_token	*tokenizing(char *str);

#endif
