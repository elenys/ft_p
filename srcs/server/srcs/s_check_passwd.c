#include "serveur.h"

static void		get_user(char **user, char **pwd)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_strsplit(*user, ':');
	free(*user);
	*user = ft_strdup(tab[0]);
	*pwd = ft_strdup(tab[1]);
	while (tab[i++])
		free(tab[i]);
	free(tab);
}

static char		*look_user(char *user)
{
	int		fd;
	int		ret;
	char	*line;
	char	*pwd;

	ret = 1;
	fd = open("./pass.txt", O_RDONLY);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		get_user(&line, &pwd);
		if (!ft_strcmp(line, user))
		{
			free(line);
			return (pwd);
		}
		free(line);
		free(pwd);
	}
	return (NULL);
}

static int		compare_passwd(char *pwd, char *e_pwd)
{
	if (!ft_strcmp(crypto(pwd), e_pwd))
		return (1);
	return (0);
}

int				check_user(t_auth check)
{
	char	*pwd;

	pwd = look_user(check.user);
	if (!pwd || !compare_passwd(check.pwd, pwd))
		return (-1);
	return (0);
}
