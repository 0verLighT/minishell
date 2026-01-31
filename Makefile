CC			:= cc
CFLAGS		:= -MP -MMD -Wall -Werror -Wextra -g
LIBFT_DIR	:= ./subprojects/libft
LDFLAGS		:= -L$(LIBFT_DIR)
LDLIBS		:= -lft -lreadline
NAME		:= minishell
INCLUDES	:= -Iincludes -I$(LIBFT_DIR)/includes
BUILD_DIR	:= .build
PREFIX		?= ~/.local/bin

SRC			:= main.c

SRCS = \
	$(addprefix src/, $(SRC)) \

OBJS		:= $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.d)

-include $(DEPS)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) -j8
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

re: fclean
	$(MAKE) all

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf .build/

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

install: 
	$(MAKE) all
	mv $(NAME) $(PREFIX)

.PHONY: all re fclean clean
