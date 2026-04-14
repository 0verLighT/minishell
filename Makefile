CC				:= cc
CFLAGS			:= -MP -MMD -Wall -g -Werror -Wextra #-fsanitize=address
LIBFT_DIR		:= ./subprojects/libft
LDFLAGS			:= -L$(LIBFT_DIR)
LDLIBS			:= -lft -lreadline
NAME			:= minishell
INCLUDES		:= -Iincludes -I$(LIBFT_DIR)/includes -Isrc/tokenizer
PREFIX			?= ~/.local/bin

SRC				:= main.c
BUILTIN			:= ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c
BUILTIN_HELPER	:= builtin_utils.c cd_utils.c exit_utils.c export_utils.c
CTX				:= init.c
SIGNALS			:= signal.c
UTILS			:= ft_getenv.c free_env.c ft_isoperator.c
PARSER			:=																		\
				ast_node_helper.c parser_free.c parse_command_helper.c					\
				parse_command.c pipe_parse.c redirection_create.c 						\
				redirection_parse.c redirection_utils.c simple_command_utils.c			\
				token_cursor.c
TOKENIZER		:= tokenizer.c tokenizer_utils.c init_type_tokens.c
EXEC			:= exec_builtin_helper.c exec_builtin.c exec_cmd.c exec_core.c			\
				exec_error.c exec_expand.c exec_external.c exec_fd.c exec_heredoc.c		\
				exec_logical.c exec_pipe.c exec_redir.c exec_wait.c applies_expand.c	\
				exec_expand_helper.c													\

SOURCES =													\
	$(addprefix src/, $(SRC))								\
	$(addprefix src/builtin/, $(BUILTIN))					\
	$(addprefix src/builtin/helper/, $(BUILTIN_HELPER))		\
	$(addprefix src/exec/, $(EXEC))							\
	$(addprefix src/ctx/, $(CTX))							\
	$(addprefix src/parser/, $(PARSER))						\
	$(addprefix src/signals/, $(SIGNALS))					\
	$(addprefix src/tokenizer/, $(TOKENIZER))				\
	$(addprefix src/utils/, $(UTILS))						\

OBJS			:= $(SOURCES:%.c=%.o)
DEPS			:= $(SOURCES:%.c=%.d)


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
