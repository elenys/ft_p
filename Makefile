SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)
	@make -C libft 

$(SERVER):
	@make -C server

clean:
	@make clean -C server
	@make clean -C libft

fclean: clean
	@make fclean -C server
	@make fclean -C libft

re: fclean all
	@make re -C server

.PHONY: clean fclean cclean all re
