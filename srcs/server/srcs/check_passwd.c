#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "./libft/includes/libft.h"
#include "./libft/includes/get_next_line.h"

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
	char	*line;
	char	*pwd;

	fd = open("./pass.txt", O_RDONLY);
	while (get_next_line(fd, &line) && fd != -1)
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

int				check_user(t_auth *check)
{
	char	*pwd;

	pwd = look_user(check_user);
	if (!pwd || !compare(pwd, check->pwd))
		return (-1);
	return (0);
}
