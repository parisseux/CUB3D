NAME = cub3D
NAME_BONUS = cub3D_bonus

HEADERS = ./inc
BONUS_HEADERS = ./bonus/inc
SRC_DIR = ./src
BONUS_SRC_DIR = ./bonus/src
PARSING_DIR = $(SRC_DIR)/parsing
BONUS_PARSING_DIR = $(BONUS_SRC_DIR)/parsing
MLX_DIRR = $(SRC_DIR)/mlx
BONUS_MLX_DIRR = $(BONUS_SRC_DIR)/mlx
RAYCASTING_DIR = $(SRC_DIR)/raycasting
BONUS_RAYCASTING_DIR = $(BONUS_SRC_DIR)/raycasting
LIBFT_DIR = ./libft
OBJ_DIR = ./obj
BONUS_OBJ_DIR = ./bonus/obj

CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude -I$(HEADERS) -g3
BONUS_CFLAGS = -Wall -Werror -Wextra -Iinclude -I$(BONUS_HEADERS) -g3

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    MLX_DIR = ./minilibx_macos
    LDFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -lreadline
    CFLAGS += -I$(MLX_DIR)
    BONUS_CFLAGS += -I$(MLX_DIR)
endif

ifeq ($(UNAME_S), Linux)
    MLX_DIR = ./minilibx-linux
    LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lreadline
    CFLAGS += -I$(MLX_DIR)
    BONUS_CFLAGS += -I$(MLX_DIR)
endif

# === SOURCES ===

SRC_DIRS = $(SRC_DIR) $(PARSING_DIR) $(MLX_DIRR) $(RAYCASTING_DIR)
SRC_FILES = $(sort $(foreach dir,$(SRC_DIRS),$(shell find $(dir) -name '*.c')))
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_SRC_DIRS = $(BONUS_SRC_DIR) $(BONUS_PARSING_DIR) $(BONUS_MLX_DIRR) $(BONUS_RAYCASTING_DIR)
BONUS_SRC_FILES = $(sort $(foreach dir,$(BONUS_SRC_DIRS),$(shell find $(dir) -name '*.c')))
BONUS_OBJ_FILES = $(BONUS_SRC_FILES:$(BONUS_SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# === COULEURS ===

ROSE = \033[35m
GREEN = \033[1;92m
RESET = \033[0m

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

bonus: $(LIBFT_LIB) $(MLX_LIB) $(NAME_BONUS)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS)
	@echo "$(ROSE)Compilation réussie. Let's play!!!$(RESET)"

$(NAME_BONUS): $(BONUS_OBJ_FILES)
	@$(CC) $(BONUS_CFLAGS) -o $(NAME_BONUS) $(BONUS_OBJ_FILES) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS)
	@echo "$(ROSE)Compilation bonus réussie. Let's play with minimap!!!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(BONUS_CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean:
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "Nettoyage $(GREEN)[OK]$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re