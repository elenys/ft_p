#include "libft.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <types.h>

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putendl(" <addrs> <port>");
	exit(-1);
}

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return(-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("connect");
		ft_putendl("Error Connect");
		exit(2);
	}
	return (sock);
}

int		main(int ac, char **av)
{
	int					sock;
	int					port;
	int					ret;
	char				phrase[256];

	ret = 0;
	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	write(sock, "Connexion clienti\n", 17);
	while (!ret)
	{
		ft_putstr("Entrez votre phrase : ");
		fgets(phrase, 255, stdin);
		phrase[strlen(phrase) - 1] = '\0';
		if (!ft_strcmp(phrase, "EXIT"))
		{
			ret = 1;
			ft_putendl("Exit client");
		}
		write(sock, phrase, ft_strlen(phrase));
	}
	close(sock);
	return (0);
}
