CC = cc 
NAME = cub3D 
MLX = ./mlx/libmlx.a 
LIBFT = ./libft/libft.a

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz 
CFLAGS = -Wall -Wextra -Werror -D PATH="\"$(shell pwd)\"" -Iincludes -Imlx 

OBJ_DIR = objs
SRC_DIR = srcs
ENV_DIR = env
PARSING_DIR = parsing
RENDER_DIR = rendering
GAME_DIR = gameplay

ENV = $(addprefix $(ENV_DIR)/, init.c utils.c free.c error.c)
PARSING = $(addprefix $(PARSING_DIR)/, parser.c checker.c utils.c env.c lst_map.c setter.c errors.c)
RENDER = $(addprefix $(RENDER_DIR)/, renderer.c utils.c raycasting.c texture.c map.c)
GAMEPLAY = $(addprefix $(GAME_DIR)/, movement.c)
SRCS = $(addprefix $(SRC_DIR)/, $(ENV) $(PARSING) $(GAMEPLAY) $(RENDER) main.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: ${NAME}

${NAME}: ${OBJS}
	@make -C mlx
	@make -C libft
	${CC} ${CFLAGS} ${MLX_FLAGS} ${OBJS} -o ${NAME} ${LIBFT} ${MLX}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(ENV_DIR)
	mkdir -p $(OBJ_DIR)/$(PARSING_DIR)
	mkdir -p $(OBJ_DIR)/$(GAME_DIR)
	mkdir -p $(OBJ_DIR)/$(RENDER_DIR)

clean:
	@make clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	@make clean -C mlx
	rm -f ${LIBFT}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
