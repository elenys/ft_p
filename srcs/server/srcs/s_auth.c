#include "serveur.h"

static t_auth	add_to_struct(char *str_auth)
{
	char	**tab;
	t_auth	auth;

	tab = ft_strsplit(str_auth, ':');
	auth.user = ft_strdup(tab[0]);
	auth.pwd = ft_strdup(tab[1]);
	auth.type = ft_atoi(tab[2]);
	//free_2d_tab((void **)tab);
	printf("login %s, password%s\n", auth.user, auth.pwd);
	return(auth);
}

static char		*get_client_auth(int sock)
{
	int		ret;
	char	*buf;

	buf = ft_strnew(24);
	ret = 0;
	while (ret == 0)
	{
		printf("OUIL\n");
		ret = recv(sock, buf, 24, 0);
	}
	printf("J'ai recus %s\n", buf);
	return (buf);
}

char			*auth(int sock)
{
	int		ret;
	char	*user;
	char	*str_auth;
	t_auth	auth;

	ret = 0;
	user = NULL;
	str_auth = get_client_auth(sock);
	auth = add_to_struct(str_auth);
	printf("%s\n",auth.user);
	if (auth.type == CREATE)
		ret = add_user(auth);
	if (ret == 0)
		ret = check_user(auth);
	if (ret == 0)
		user = ft_strdup(auth.user);
	printf("user =%s\n", user);
	free_auth_struct(auth);
	return (user);
}
