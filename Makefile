CC				:= cc
CFLAGS			:= -MP -MMD -Wall -Werror -Wextra -g #-fsanitize=address
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
SIGNALS			:= check_sig.c signal.c
UTILS			:= ft_getenv.c free_env.c
INPUT			:= fish.c
#TOKENIZER		:= tokenizer_utils.c tokenizer_utils_two.c

SOURCES			:=									\
	$(addprefix src/, $(SRC))						\
	$(addprefix src/builtin/, $(BUILTIN))			\
	$(addprefix src/builtin/helper, $(BUILTIN_HELPER))	\
	$(addprefix src/ctx/, $(CTX))					\
	$(addprefix src/input/, $(INPUT))				\
	$(addprefix src/signals/, $(SIGNALS))			\
	$(addprefix src/utils/, $(UTILS))				\
#	$(addprefix src/tokenizer/, $(TOKENIZER))		\

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
