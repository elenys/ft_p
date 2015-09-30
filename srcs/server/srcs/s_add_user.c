#include "serveur.h"


static int				add_user(t_auth user)
{
	int		fd;
	char	*ret;
	char	*add;

	fd = open(USER_FILE, O_WRONLY | O_APPEND);
	if (fd < 0)
		return (-1);
	ret = ft_strjoin(user.user, ":");
	add = ft_strjoin(ret, crypto(user.pwd));
	free(ret);
	ret = ft_strjoin(add, "\n");
	write(fd, ret, ft_strlen(ret));
	free(ret);
	free(add);
	close(fd);
	return (0);
}

/*
int			add_connected(t_auth user, struct sockaddr_in sock_info)
{
}*/

int			create_user(t_auth user, int sock, struct sockaddr_in sock_info)
{
	t_auth auth;

	(void)sock_info;
	auth = user_exist(user.user);
	ft_putendl(user.user);
	if (auth.user == NULL)
	{
		ft_putendl("User successfully added");
		if (add_user(user) >= 0)
		{
			send_connexion_message(CONNECTION_SUCCES, sock);
			return (0);
		}
		else
			ft_putendl("Error: can't open file");
	}
	send_connexion_message(USER_ALLREADY_EXIST, sock);
	return (-1);
}
