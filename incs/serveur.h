/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 11:05:08 by bmartins          #+#    #+#             */
/*   Updated: 2015/09/03 15:21:03 by bmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

#include "ftp.h"
#include <sys/wait.h>

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
int		check_user(t_auth check);
int		add_user(t_auth user);

char	*auth(int sock);
char	*crypto(char *str);

#endif
