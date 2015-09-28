#include "serveur.h"

int			add_user(t_auth user)
{
	int		fd;
	char	*ret;
	char	*add;

	ret = ft_strjoin(user.user, ":");
	add = ft_strjoin(ret, crypto(user.pwd));
	//free(ret);
	ret = ft_strjoin(add, "\n");
	fd = open("./pass.txt", O_WRONLY | O_APPEND);
	write(fd, ret, ft_strlen(ret));
	//free(ret);
	//free(add);
	close(fd);
	return (0);
}
