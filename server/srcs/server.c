#include "libft.h"
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 42);
	return (sock);
}

int		main(int ac, char **av)
{
	int					sock;
	int					port;
	int					cs;
	size_t				cslen;
	struct sockaddr_in	s_info;
	int					r;
	char				buf[1024];

	if (ac != 2)
		usage(av[0]);
	port = ft_atoi(av[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr*)&s_info, &cslen);
	r = read(cs, buf, 1023);
	if (r > 0)
	{
		buf[r] = 0;
		ft_putstr("received ");
		ft_putnbr(r);
		ft_putstr("bytes: ");
		ft_putendl(buf);
	}
	close(cs);
	close(sock);
	return (0);
}
