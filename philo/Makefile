#cores
BG_YELLOW = \033[43m
YELLOW    = \033[33m
WHITE     = \033[97m
BLACK     = \033[30m
CINZA     = \033[47m\033[30m
RESET     = \033[0m

#flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I. -Iincludes
EXEC = philo
OBJ_DIR = Obj

#src_arquives
SRCS_DIR = src/philo.c src/teste.c
SRC_AUX = aux/ft_atoi.c aux/ft_putstr_fd.c

SRC = $(SRC_AUX) $(SRCS_DIR)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(EXEC)

$(EXEC): $(OBJ) $(MLX_ARQ)
		@echo "$(BG_YELLOW)$(BLACK)[CREATE] FOOD TIME *-* $(EXEC)$(RESET)"
		@$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
		@mkdir -p $(dir $@)
		@echo "$(YELLOW)[COMPILE] $<$(RESET)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(MLX_ARQ):
		@cd $(dir $@) && make

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		@echo " 🗑️  Andou, andou e no lixo parouu!"
		@rm -f $(EXEC)

git:
	@git add .
	@git commit -m "$(m)"
	@cd ..
	@git push

norma:
		@norminette .

re: fclean all

.PHONY: re fclean clean all