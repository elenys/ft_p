#include "serveur.h"

static t_auth parse_user(char *str_auth, char *user)
{
	t_auth	auth;
	char	**tab;

	tab = ft_strsplit(str_auth, ':');
	if (ft_strcmp(tab[0], user))
	{
		auth.user = ft_strdup(tab[0]);
		auth.pwd = ft_strdup(tab[1]);
	}
	else
		auth.user = NULL;
	free_2d_tab((void **)tab);
	return (auth);
}

t_auth			user_exist(char *user)
{
	int		fd;
	char	*line;
	t_auth	auth;

	fd = open(USER_FILE, O_RDONLY);
	while (get_next_line(fd, &line) >= 0 && auth.user != NULL)
		auth = parse_user(line, user);
	free(line);
	close(fd);
	return (auth);
}

static int		compare_passwd(char *pwd, char *e_pwd)
{
	if (!ft_strcmp(crypto(pwd), e_pwd))
		return (-1);
	return (0);
}

int				connect_user(t_auth check, int sock, struct sockaddr_in sock_info)
{
	t_auth	auth;

	(void)sock_info;
	auth = user_exist(check.user);
	if (auth.user == NULL)
	{
		send_connexion_message(USER_DOES_NOT_EXIST, sock);
		return (-1);
	}
	if (compare_passwd(check.pwd, auth.pwd) >= 0)
	{
		send_connexion_message(INVALID_PASSWORD, sock);
		return (-1);
	}
	send_connexion_message(CONNECTION_SUCCES, sock);
	//free authM#
	return (0);
}
