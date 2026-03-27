/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 02:31:28 by jdessoli          #+#    #+#             */
/*   Updated: 2026/03/28 00:28:47 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tokenizer.h
 */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include "utils.h"

/**
 * @brief enum of type for token
 */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
}	t_token_type;

/**
 * @brief Allows to take chunks of the input, with a precise starting and ending 
 * point
 * @param ptr
 * @param len
 */
typedef struct s_node_token
{
	char	*ptr;
	size_t	len;
}	t_node_token;

/**
 * @brief A token is a chunk of the input with an index That way, we can  
 * work on isolated chunks by giving the index
 * @param index
 * @param type
 * @param content
*/
typedef struct s_token
{
	size_t			index;
	t_token_type	type;
	t_node_token	content;
}	t_token;

//tokenizer.c
/**
 * @brief Get the length of a token starting at pos
 * @param str
 * @param pos
 * @return length of token starting at pos
 */
size_t			get_token_len(char *str, size_t pos, size_t *content_len);
/**
 * @brief Allocate and fill a token
 * @param token
 * @param str
 * @param pos
 * @param index
 * @return 0 on error, 1 on succesfully
 */
int				fill_token(t_token *token, char *str, size_t *pos, int index);
/**
 * @brief Fill the token one by one
 * @param token
 * @param str
 * @param token_count
 * @return 0 on error, 1 sucessfully
 */
int				process_tokens(t_token *tokens, char *str, size_t token_count);
/**
 * @brief Main function of tokenzier
 * @param str
 * @return prompt in token struct
 */
t_token			*tokenizing(char *str);

//tokenizer_utils.c
/**
 * @brief Skip space in string
 * @param str
 * @return lenght of speace in the start of str
 */
size_t			strskip(char *str);
/**
 * @brief Count number of token
 * @param str
 * @return number of token
 */
size_t			count_token(char *str);
/**
 * @brief create an node of token
 * @param str
 * @param i
 * @return node of token
 */
t_node_token	*token_maker(char *str);
/**
 * @brief Free the token struct
 */
void			free_tokens(t_token *tokens, size_t token_nb);

#endif
