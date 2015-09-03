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

int		create_server(int port);

void	usage(char *str);
void	s_error(char *error);
void	s_error_fork(int sock);

#endif
