#include "serveur.h"

void	free_2d_tab(void **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	send_connexion_message(int msg, int sock)
{
	char	*str;

	str = ft_itoa(msg);
 	if (msg == CONNECTION_SUCCES)
		ft_putendl("Connection succes");
	else if (msg == USER_ALLREADY_EXIST)
		ft_putendl("User alleady exist");
	else if (msg == INVALID_PASSWORD)
		ft_putendl("Wrong Password");
	else if (msg == USER_DOES_NOT_EXIST)
		ft_putendl("User does not exist");
	write(sock, str, ft_strlen(str));
	write(sock, "\n", 1);
	free(str);
}
