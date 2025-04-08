NAME = micro_cub3d
SRCS = main.c utils.c raycasting.c
CFLAGS = -Wall -Werror -Wextra
OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBX = minilibx_linux
MLXFLAGS_LINUX = -L ${LIBX} -lmlx -lX11 -lXext -lm

all: ${NAME}

${NAME}: ${OBJS}
	@make all -s -C ${LIBX}
	@cc ${CFLAGS} ${OBJS} ${MLXFLAGS_LINUX} -o ${NAME}
	@clear

${OBJ_DIR}/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@cc ${CFLAGS} -c $< -o $@

clean:
	@make clean -s -C ${LIBX}
	@rm -rf ${OBJ_DIR}
	@clear

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
