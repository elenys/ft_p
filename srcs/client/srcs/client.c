/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 11:07:31 by bmartins          #+#    #+#             */
/*   Updated: 2015/09/30 15:24:06 by aiwanesk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
		ft_putendl("error : connect");
		exit(2);
	}
	return (sock);
}


int		main(int ac, char **av)
{
	int					sock;
	int					port;
	int					ret;
//	int					rv;
//	char				*phrase;

	ret = 0;
	if (ac != 3)
		usage(av[0]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	auth(sock);
	write(sock, "Connection client\n", 17);
	/*while (!ret)
	{
		ft_putstr("Entrez votre phrase: ");
		while ((rv = get_next_line(0, &phrase)) > 1)
			;
		phrase[ft_strlen(phrase)] = 0;
		if (!ft_strcmp(phrase, "EXIT"))
		{
			ret = 1;
			ft_putendl("Exit client");
		}
		write(sock, phrase, ft_strlen(phrase));
		ft_strdel(&phrase);
	}*/
	close(sock);
	return (0);
}
