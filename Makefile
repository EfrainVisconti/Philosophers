# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 18:53:27 by eviscont          #+#    #+#              #
#    Updated: 2024/06/06 20:10:25 by eviscont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definir colores
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

# Comandos
# -g para debugear con lldb
CFLAGS = -Wall -Wextra -Werror -pthread #-g3 -fsanitize=thread

# Nombre ejecutable
NAME = philo

# Ficheros
SRC_FILES = main utils
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# Directorios
SRC_DIR = src/
OBJ_DIR = obj/

# Reglas
all: $(NAME)

# Compilar
$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)PROGRAM HAS BEEN COMPILED$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling...$<$(NC)"
	@gcc $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW)Done!$(NC)"

# Eliminar temporales
clean:
	@rm -f -r $(OBJ_DIR)
	@echo "$(RED)OBJECTS CLEANED!$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

re: fclean all