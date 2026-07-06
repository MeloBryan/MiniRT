# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 14:17:41 by bmelo             #+#    #+#              #
#    Updated: 2026/06/13 02:29:53 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	MiniRT
CC				=	cc
CFLAGS			=	-O3 -Wall -Wextra -Werror -lm -Iincludes -Iminilibx-linux -MMD -MP

SRC_DIR			=	src
OBJ_DIR			=	objs

MLX_PATH		=	minilibx-linux
MLX				=	$(MLX_PATH)/libmlx.a
LIBFT_PATH		=	libft
LIBFT			=	$(LIBFT_PATH)/libft.a

FILES			=	main.c \
				Image/window_handler.c \
				Image/renderer.c \
				Vectors/Normalization.c \
				Vectors/Vec_Length.c \
				Vectors/Dot_Product.c \
				Vectors/Cross_Vec.c \
				Parsing/free.c \
				Parsing/parse_ambient.c \
				Parsing/parse_line.c \
				Parsing/parse_camera.c \
				Parsing/parse_light.c \

SRCS			=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJS_MANDATORY	=	$(FILES:%.c=$(OBJ_DIR)/%.o)

DEPS			=	$(OBJS_MANDATORY:%.o=%.d)

LIBS			=	$(LIBFT) $(MLX) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS_MANDATORY)
	@$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBS) -o $(NAME)
	@lines=$$(tput lines); \
	while [ $$lines -gt 0 ]; do \
		printf "\033[1A\033[K"; \
		sleep 0.05; \
		lines=$$((lines - 1)); \
	done

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Compilation de la Libft ..."
	@$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	@echo "Compilation de la Minilibx ..."
	-@$(MAKE) -C $(MLX_PATH) all

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@lines=$$(tput lines); \
	while [ $$lines -gt 0 ]; do \
		printf "\033[1A\033[K"; \
		sleep 0.05; \
		lines=$$((lines - 1)); \
	done

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(MLX_PATH)/*.gen
	@lines=$$(tput lines); \
	while [ $$lines -gt 0 ]; do \
		printf "\033[1A\033[K"; \
		sleep 0.05; \
		lines=$$((lines - 1)); \
	done

re: fclean all

.PHONY: all bonus clean fclean re
-include $(DEPS)
