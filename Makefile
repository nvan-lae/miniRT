# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvan-der <jvan-der@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 00:00:00 by jvan-der          #+#    #+#              #
#    Updated: 2025/09/09 13:31:26 by nvan-lae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# Directories
SRC_DIR = src
INC_DIR = inc
LIBFT_DIR = $(INC_DIR)/Libft
MLX_DIR = $(INC_DIR)/minilibx

# Source files
SRC_FILES = main.c \
			scene_check/scene_check.c \
			scene_check/type_check.c \
			scene_check/validate_acl.c \
			scene_check/validate_shapes.c \
			scene_check/validation_help.c \
			scene_check/array.c \
			parsing/parse_scene.c \
			parsing/parse_objects.c \
			parsing/parse_utils.c \
			parsing/ft_atof.c \
			parsing/parse_shapes.c \
			parsing/parse_material.c \
			parsing/count_malloc_objects.c \
			objects/sphere/sphere_utils.c \
			objects/plane/plane_utils.c \
			objects/cylinder/cylinder_utils.c \
			objects/paraboloid/paraboloid_utils.c \
			math/vector_ops/vector_ops.c \
			math/vector_ops/vector_ops2.c \
			math/intersection/intersect.c \
			math/intersection/paraboloid_intersect.c \
			math/intersection/cylinder_intersect.c \
			math/ray_math.c \
			math/trace_ray.c \
			math/lighting/shadow.c \
			math/lighting/shading_utils.c \
			math/lighting/lighting.c \
			math/lighting/refraction.c \
			math/material_effects.c \
			math/math_utils.c \
			math/mapping/uv_mapping.c \
			math/mapping/bump_mapping.c \
			utils/utils.c \
			utils/key_hook.c \
			utils/error.c \
			utils/free.c \
			utils/color.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(MLX):
	@echo "$(GREEN)Building minilibx...$(RESET)"
	@make -C $(MLX_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
