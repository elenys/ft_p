#include "serveur.h"

static t_auth parse_user(char *str_auth, char *user)
{
	t_auth	auth;
	char	**tab;

	tab = ft_strsplit(str_auth, ':');
	printf("line = %s - user_verif = %s\n", tab[0], user);
	if (!ft_strcmp(tab[0], user))
	{
		auth.user = ft_strdup(tab[0]);
		auth.pwd = ft_strdup(tab[1]);
	}
	else
		auth.user = NULL;
	free_2d_tab((void **)tab);
	printf("%s\n",auth.user);
	return (auth);
}

t_auth			user_exist(char *user)
{
	int		fd;
	char	*line;
	t_auth	auth;

	fd = open(USER_FILE, O_RDONLY);
	while ((get_next_line(fd, &line) >= 0) && (auth.user == NULL))
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
	ft_putendl("FCT_CONNECT_USER");
	auth = user_exist(check.user);
	
	if (!ft_strcmp(auth.user, check.user))
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
