# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TODO.md                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdessoli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/14 01:27:27 by jdessoli          #+#    #+#              #
#    Updated: 2026/02/14 03:21:20 by jdessoli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Parser logic:

Step 1: Create a AST Nodes Data Structure (what will be returned)

Step 2: Implement a Token Cursor (makes parsing logic cleaner)

Step 4: Handle Redirections

Step 5: Handle Pipes

Step 6: Handle Logical Operators

Step 7: Syntax Validation

Check for errors:

    Pipes/operators at the beginning or end
    Missing filenames after redirections
    Two operators in a row
    Unclosed quotes (might be done in tokenizer)

Step 8: Build and Return the struct

