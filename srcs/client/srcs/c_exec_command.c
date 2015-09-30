/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_exec_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwanesk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 13:46:39 by aiwanesk          #+#    #+#             */
/*   Updated: 2015/09/30 14:46:17 by aiwanesk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		cmd_is_valid(char *str, int sock)
{
	if (ft_strcmp(str, "ls") == 0)
		execv(getcwd(str, ft_strlen(str)), &str);
	sock = sock - 1;
}

void			exec_command(int sock)
{
	char		*cmd;

	printf ("JE SUIS BIEN LA CHIEN\n");
	while (1)
	{
		get_next_line(0, &cmd);
		printf ("test cmd[%s]\n", cmd);
		if (ft_strcmp(cmd, "quit") == 0)
			exit(0);
		else
			cmd_is_valid(cmd, sock);
	}
}
