#include "serveur.h"

static t_auth	add_to_struct(char *str_auth)
{
	char	**tab;
	t_auth	auth;

	tab = ft_strsplit(str_auth, ':');
	auth.user = ft_strdup(tab[0]);
	auth.pwd = ft_strdup(tab[1]);
	auth.type = ft_atoi(tab[2]);
	free_2d_tab((void **)tab);
	free(str_auth);
	return(auth);
}

static char		*get_client_auth(int sock)
{
	int		ret;
	char	*buf;

	buf = ft_strnew(24);
	ret = 0;
	while (ret == 0)
		ret = recv(sock, buf, 24, 0);
	return (buf);
}

void			auth(int sock, struct sockaddr_in sock_info)
{
	int		ret;
	char	*str_client_auth;
	t_auth	auth;

	ret = 0;
	while (ret == 0)
	{
		str_client_auth = get_client_auth(sock);
		auth = add_to_struct(str_client_auth);
		if (auth.type == CREATE)
			create_user(auth, sock, sock_info);
		else if (auth.type == CONNECTION)
			connect_user(auth, sock, sock_info);
		else
			ft_putendl("error recuperation");
	}
	free_auth_struct(auth);
}
