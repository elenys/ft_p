/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_socket.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:19:56 by bmartins          #+#    #+#             */
/*   Updated: 2015/09/03 15:21:06 by bmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*protocole;
	struct sockaddr_in	adr_serv;

	protocole = getprotobyname("tcp");
	if (protocole == 0)
		s_error("to get protocole");
	sock = socket(PF_INET, SOCK_STREAM, protocole->p_proto);
	adr_serv.sin_family = AF_INET;
	adr_serv.sin_port = htons(port);
	adr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&adr_serv, sizeof(adr_serv)) == -1)
		s_error("to bind the socket");
	if (listen(sock, 10) == -1)
		s_error("to listen the socket");
	return (sock);
}
