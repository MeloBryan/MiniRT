# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmelo <bmelo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 08:27:26 by bmelo             #+#    #+#              #
#    Updated: 2026/03/18 12:16:11 by bmelo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
				ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
				ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
				ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c \
				ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
				ft_lstmap_bonus.c ft_printf.c ft_printf_utils.c \
				ft_printf_functions.c get_next_line.c ft_atof.c

SRCS_DIR	=		src
SRCS		=		$(addprefix $(SRCS_DIR)/, $(SRC))
OBJ_DIR		=		objs
OBJS		=		$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS		=		$(OBJS:.o=.d)
NAME		=		libft.a
CC			=		cc
CFLAGS		=		-Wall -Wextra -Werror -Iincludes -MMD -MP

GREEN = \033[38;2;41;169;41m]
NC = \033[0m]

define ECHO_SUCCESS
	@echo "$(GREEN)[Libft] Compilation success!$(NC)"
endef

$(OBJ_DIR)/%.o: 	$(SRCS_DIR)/%.c
					@mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJS)
					ar rc $(NAME) $(OBJS)
					$(ECHO_SUCCESS)

all:				$(NAME)

clean:
					rm -rf $(OBJ_DIR)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re bonus

-include $(DEPS)
