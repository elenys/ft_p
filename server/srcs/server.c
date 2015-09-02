#include "libft.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putendl(" <port>");
	exit(-1);
}

int		create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("bind");
		exit(2);
	}
	if (listen(sock, 10) == -1)
	{
		perror("listen");
		exit(2);
	}
	return (sock);
}

int		main(int ac, char **av)
{
	size_t				counter;
	int					sock;
	int					port;
	unsigned int		cslen;
	struct sockaddr_in	s_info;
	int					r;
	char				buf[1024];

	counter = 0;
	if (ac != 2)
		usage(av[0]);
	port = ft_atoi(av[1]);
	sock = create_server(port);
	
	int pid;
	int new;
	while (1)
	{
		new = accept(sock, (struct sockaddr*)&s_info, &cslen);
		if ((pid = fork()) == -1)
		{
			close(new);
		}
		else if (pid > 0)
		{
			counter++;
			ft_putendl("here-1");
			close(new);
		}
		else if (pid == 0)
		{
			while (strcmp(buf, "EXIT"))
			{
				r = recv(new, buf, 1023, 0);
				if (r < 0)
				perror("recv");
				buf[r] = 0;
				if (r > 0)
				{
					ft_putstr("received ");
					ft_putnbr(r);
					ft_putstr(" bytes: ");
					ft_putendl(buf);
				}
			}
		}
	}
	close(new);
	close(sock);
	return (0);
}
