/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartins <bmartins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/03 14:25:38 by bmartins          #+#    #+#             */
/*   Updated: 2015/09/03 15:17:30 by bmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	s_error(char *error)
{
	ft_putstr("Error: ");
	ft_putendl(error);
	exit(EXIT_FAILURE);
}

void	s_error_fork(int sock)
{
	ft_putendl("Error: can't fork a new server");
	close(sock);
	exit(EXIT_FAILURE);
}

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putendl(" <port>");
	exit(EXIT_FAILURE);
}
