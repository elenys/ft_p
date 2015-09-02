SERVER = serveur
CLIENT = client
LIBFT  = ./libft/libft.a

all: $(LIBFT) $(SERVER)

$(SERVER):
	@make -C server

$(LIBFT):
	@make -C libft

clean:
	@make clean -C server
	@make clean -C libft

fclean: clean
	@make fclean -C server
	@make fclean -C libft

re: fclean all
	@make re -C server

.PHONY: clean fclean cclean all re
