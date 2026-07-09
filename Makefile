# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edefoy <edefoy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 14:17:41 by bmelo             #+#    #+#              #
#    Updated: 2026/07/09 14:57:41 by edefoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#   PROGRAM                                                                    #
# ---------------------------------------------------------------------------- #

NAME        := MiniRT

# ---------------------------------------------------------------------------- #
#   LIBRARIES                                                                  #
# ---------------------------------------------------------------------------- #

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

MLX_DIR     := minilibx-linux
MLX         := $(MLX_DIR)/libmlx.a

# ---------------------------------------------------------------------------- #
#   COMPILER & FLAGS                                                           #
#                                                                              #
#   CFLAGS   : compilation only                                                #
#   CPPFLAGS : preprocessor (include paths, dependency generation)             #
#   LDFLAGS  : linker search paths                                             #
#   LDLIBS   : libraries to link against (-lm = math, X11/Xext = MiniLibX)     #
# ---------------------------------------------------------------------------- #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -O3
CPPFLAGS    := -Iincludes -I$(MLX_DIR) -Ilibft/includes -MMD -MP
LDFLAGS     := -L$(LIBFT_DIR) -L$(MLX_DIR)
LDLIBS      := -lft -lmlx -lXext -lX11 -lm

# ---------------------------------------------------------------------------- #
#   SOURCES & OBJECTS                                                          #
#                                                                              #
#   Objects mirror src/ inside objs/ (src/a/b.c -> objs/a/b.o).                #
#   .d files are generated next to objects by -MMD -MP and included at the     #
#   bottom, so editing a header recompiles exactly the files that use it.      #
# ---------------------------------------------------------------------------- #

SRC_DIR     := src
OBJ_DIR     := objs

SRC         := main.c \
               Image/window_handler.c \
               Image/renderer.c \
               Image/color.c \
               Rayon/rayon.c \
               Parsing/parse_line.c \
               Parsing/parse_utils.c \
               Parsing/parse_ambient.c \
               Parsing/parse_camera.c \
               Parsing/parse_light.c \
               Parsing/parse_sphere.c \
               Parsing/parse_plane.c \
               Parsing/parse_cylinder.c \
               Parsing/free.c \
               Parsing/object.c \
               Vectors/Addition.c \
               Vectors/Soustraction.c \
               Vectors/Multiplication.c \
               Vectors/Normalization.c \
               Vectors/Vec_Length.c \
               Vectors/Dot_Product.c \
               Vectors/Cross_Vec.c

SRCS        := $(addprefix $(SRC_DIR)/, $(SRC))
OBJS        := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:%.o=%.d)

# ---------------------------------------------------------------------------- #
#   TESTS (not graded, see subject: Common Instructions)                       #
# ---------------------------------------------------------------------------- #

TEST_NAME   := test_parsing
TEST_SRC    := tests/test_parsing.c
OBJS_NOMAIN := $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

# ---------------------------------------------------------------------------- #
#   RULES                                                                      #
# ---------------------------------------------------------------------------- #

all: $(NAME)

# Link. $(NAME) depends on real files only -> no relink when nothing changed.
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "==> $(NAME) ready"

# Compile. '| $(OBJ_DIR)' is an order-only prerequisite: the directory must
# exist, but its timestamp never triggers a rebuild.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "==> building libft"
	@$(MAKE) -C $(LIBFT_DIR)

# Build only the MiniLibX LIBRARY, never its demo programs: the demos
# need extra libs (-lbsd) and their failure would break our build.
# Recent MLX ships Makefile.gen as a template (Makefile.mk); we generate
# it exactly like ./configure does, minus the demo step.
$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "==> $(MLX_DIR)/ is missing. Clone it first:"; \
		echo "==>   git clone https://github.com/42Paris/minilibx-linux.git"; \
		exit 1; \
	fi
	@echo "==> building minilibx"
	@if [ ! -f $(MLX_DIR)/Makefile.gen ]; then \
		echo "INC=/usr/include" > $(MLX_DIR)/Makefile.gen; \
		grep -v '%%%%' $(MLX_DIR)/Makefile.mk >> $(MLX_DIR)/Makefile.gen; \
	fi
	@$(MAKE) -C $(MLX_DIR) -f Makefile.gen all

bonus: all

test: $(LIBFT) $(MLX) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TEST_SRC) $(OBJS_NOMAIN) \
		$(LDFLAGS) $(LDLIBS) -o $(TEST_NAME)
	@echo "==> ./$(TEST_NAME) ready"

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then \
		$(MAKE) -C $(MLX_DIR) -f Makefile.gen clean; fi
	@echo "==> objects removed"

fclean: clean
	rm -f $(NAME) $(TEST_NAME) $(TEST_NAME).d
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "==> binaries removed"

re: fclean all

.PHONY: all bonus test clean fclean re

# Auto-generated header dependencies ('-' = ignore if missing).
-include $(DEPS)