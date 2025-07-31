NAME = cub3D

HEADERS = ./inc
SRC_DIR = ./src
PARSING_DIR = $(SRC_DIR)/parsing
MLX_DIRR = $(SRC_DIR)/mlx
LIBFT_DIR = ./libft
OBJ_DIR = ./obj

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -I$(HEADERS) -g3

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    MLX_DIR = ./minilibx_macos
    LDFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lreadline
    CFLAGS += -I$(MLX_DIR)
endif

ifeq ($(UNAME_S), Linux)
    MLX_DIR = ./minilibx_linux
    LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lreadline
    CFLAGS += -I$(MLX_DIR)
endif

# === SOURCES ===

SRC_DIRS = $(SRC_DIR) $(PARSING_DIR) $(MLX_DIRR)
SRC_FILES = $(sort $(foreach dir,$(SRC_DIRS),$(shell find $(dir) -name '*.c')))

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# === COULEURS ===

ROSE = \033[35m
GREEN = \033[1;92m
RESET = \033[0m

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS)
	@echo "$(ROSE)Compilation réussie. Let's play!!!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "Nettoyage $(GREEN)[OK]$(RESET)"

re: fclean all

.PHONY: all clean fclean re