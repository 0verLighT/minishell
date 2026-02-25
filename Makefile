CC			:= cc
CFLAGS		:= -MP -MMD -Wall -Werror -Wextra -g #-fsanitize=address
LIBFT_DIR	:= ./subprojects/libft
LDFLAGS		:= -L$(LIBFT_DIR)
LDLIBS		:= -lft -lreadline
NAME		:= minishell
INCLUDES	:= -Iincludes -I$(LIBFT_DIR)/includes -Isrc/tokenizer
PREFIX		?= ~/.local/bin

SRC			:= main.c
BUILTIN		:= env.c
CTX			:= init.c
SIGNALS		:= check_sig.c signal.c
UTILS		:= ft_getenv.c free_env.c
INPUT		:= fish.c
PARSER		:=																		\
				ast_node_helper.c clean_up.c parse_command_helper.c					\
				parse_simple_command.c parse_pipe_parse.c redirection_create.c 		\
				redirection_parse.c simple_command_utils.c simple_command_utils.c	\
				token_cursor.c

TOKENIZER	:= tokenizer.c tokenizer_utils.c

SOURCES =										\
	$(addprefix src/, $(SRC))					\
	$(addprefix src/built-in/, $(BUILTIN))		\
	$(addprefix src/ctx/, $(CTX))				\
	$(addprefix src/input/, $(INPUT))			\
	$(addprefix src/signals/, $(SIGNALS))		\
	$(addprefix src/utils/, $(UTILS))			\
	$(addprefix src/parser/, $(PARSER))			\
	$(addprefix src/tokenizer/, $(TOKENIZER))	\

OBJS		:= $(SOURCES:%.c=%.o)
DEPS		:= $(SOURCES:%.c=%.d)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) -j8
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

re: fclean
	$(MAKE) all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

install: 
	$(MAKE) all
	mv $(NAME) $(PREFIX)

uninstall:
	rm -f $(PREFIX)/(NAME)

.PHONY: all re fclean clean install uninstall

-include $(DEPS)
