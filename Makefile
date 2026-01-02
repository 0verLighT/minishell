CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT= ./libft/libft.a
LIBFT_DIR= ./libft
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft
NAME = minishell
INCLUDES = -Iincludes -I$(LIBFT_DIR)
BUILD_DIR = .build
SRC = main.c

SRCS = \
	$(addprefix src/, $(SRC)) \

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR) -j
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

re: fclean
	$(MAKE) all

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf .build/

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

.PHONY: all re flcean clean
