# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/21 14:53:09 by tbruinem      #+#    #+#                  #
#    Updated: 2020/04/25 13:26:49 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = solver
SRC_DIR = ./src/
INCL_DIR = ./incl/
SRC =	utils.c \
		board.c \
		squarechecks.c \
		areachecks.c \
		debug.c \
		main.c \
		input.c \
		strdups.c \

CFLAGS = -Wall -Wextra -Werror
ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@ 

$(NAME): $(addprefix $(SRC_DIR), $(OBJ))
	$(CC) $(CFLAGS) -I $(INCL_DIR) $^ -o $(NAME)

clean:
	rm -rf $(addprefix $(SRC_DIR), $(OBJ))

fclean: clean
	rm -rf $(NAME)

re: fclean all
