# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/09 14:04:28 by bmartins          #+#    #+#              #
#    Updated: 2015/09/03 15:18:16 by bmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = serveur

DIR_H = ../../incs/

DIR_C = ./srcs/

DIR_O = ./objs/

FILE_C = server.c s_error.c s_socket.c s_crypto.c s_tools.c s_check_passwd.c \
	s_add_user.c s_auth.c s_auth_free.c

FILE_O = $(FILE_C:.c=.o)

SRC_C := $(addprefix $(DIR_C), $(FILE_C))

SRC_O := $(addprefix $(DIR_O), $(FILE_O))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC_O)
	@gcc -o $(NAME) $(SRC_O) -L ../../libft/ -lft
	@mv $(NAME) ../../.

$(SRC_O): $(SRC_C)
	@gcc $(FLAGS) -c $(SRC_C) -I $(DIR_H)
	@mkdir -p $(DIR_O)
	@mv $(FILE_O) $(DIR_O)

clean:
	@/bin/rm -rf $(DIR_O)

fclean: clean
	@/bin/rm -f ../$(NAME)

re: fclean all

.PHONY: clean fclean cclean all re
