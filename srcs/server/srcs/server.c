/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 11:09:35 by bmartins          #+#    #+#             */
/*   Updated: 2015/09/30 14:51:40 by bmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static void wait_for_child(int sig)
{
	(void)sig;
	while (waitpid(-1, NULL, WNOHANG) > 0);
}

static void handle(int newsock, struct sockaddr_in sock_info)
{
	int		r;
	char	buf[1024];

	auth(newsock, sock_info);
	while (strcmp(buf, "EXIT"))
	{
		r = recv(newsock, buf, 1023, 0);
		buf[r] = 0;
		if (r > 0)
		{
			ft_putstr("received ");
			ft_putnbr(r);
			ft_putstr(" bytes: ");
			ft_putendl(buf);
		}
	}
	ft_putendl("EXIT");
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = wait_for_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
		s_error("to create sigchild");
}

void	print_connexion(struct sockaddr_in sock_info)
{
	ft_putstr("Got a connection from ");
	ft_putstr(inet_ntoa(sock_info.sin_addr));
	ft_putstr( "on port ");
	ft_putnbr(htons(sock_info.sin_port));
	ft_putchar('\n');
}

static void main_serv(int sock, int newsock)
{
	int					pid;
	unsigned int		sock_size;
	struct sockaddr_in	sock_info;

	while (1)
	{
		newsock = accept(sock, (struct sockaddr*)&sock_info, &sock_size);
		if ((pid = fork()) == -1)
			s_error_fork(newsock);
		else if (pid > 0)
			close(newsock);
		else if (pid == 0)
		{
			print_connexion(sock_info);
			close(sock);
			handle(newsock, sock_info);
			exit(0);
		}
	}
}

int		main(int ac, char **av)
{
	int	sock;
	int	newsock;

	if (ac != 2)
		usage(av[0]);
	newsock = 0;
	sock = create_server(ft_atoi(av[1]));
	signal_handler();
	main_serv(sock, newsock);
	close(sock);
	return (0);
}
