/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 11:05:08 by bmartins          #+#    #+#             */
/*   Updated: 2015/09/30 14:59:10 by bmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

#include "ftp.h"
#include <sys/wait.h>

# define CONNECTION_SUCCES 0
# define USER_ALLREADY_EXIST -1
# define INVALID_PASSWORD -2
# define USER_DOES_NOT_EXIST -3

# define USER_FILE "./pass.txt"

# define CREATE 0
# define CONNECTION 1



typedef struct	s_auth
{
	char		*user;
	char		*pwd;
	int			type;
}				t_auth;

int		create_server(int port);

void	usage(char *str);
void	s_error(char *error);
void	s_error_fork(int sock);
void	free_auth_struct(t_auth auth);
void	free_2d_tab(void **tab);
void	send_connexion_message(int msg, int sock);

int		create_user(t_auth user, int sock, struct sockaddr_in sock_info);
int		connect_user(t_auth check, int sock, struct sockaddr_in sock_info);

t_auth			user_exist(char *user);

void	auth(int sock, struct sockaddr_in sock_info);
char	*crypto(char *str);

#endif
