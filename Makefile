# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/03 11:57:41 by bmartins          #+#    #+#              #
#    Updated: 2015/09/03 13:29:06 by bmartins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = serveur
CLIENT = client
LIBFT  = ./libft/libft.a

all: $(LIBFT) $(SERVER) $(CLIENT)

$(SERVER):
	@make -C srcs/server

$(CLIENT):
	@make -C srcs/client

$(LIBFT):
	@make -C libft

clean:
	@make clean -C srcs/server
	@make clean -C srcs/client
	@make clean -C libft

fclean: clean
	@make fclean -C srcs/server
	@make fclean -C srcs/client
	@make fclean -C libft

re: fclean all
	@make re -C srcs/server
	@make re -C srcs/client

.PHONY: clean fclean cclean all re
