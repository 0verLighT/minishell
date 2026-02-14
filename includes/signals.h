/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartel <amartel@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:59:23 by amartel           #+#    #+#             */
/*   Updated: 2026/02/14 04:37:17 by amartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file signals.h
 */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

void	init_sig(void);

#endif
