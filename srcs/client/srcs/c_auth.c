/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_auth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiwanesk <aiwanesk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 11:17:13 by aiwanesk          #+#    #+#             */
/*   Updated: 2015/09/30 11:50:09 by aiwanesk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	is_valid(char *str)
{
	int		i;

	i = 0;
	if (ft_strlen(str) > 10)
	{
		printf("pwd too long\n");
		return (1);
	}
	if (str[0] == '\0')
	{
		printf("i need at least one char\n");
		return (1);
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			printf("Invalid char dog fuck your syrian\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*concat(char *s1, char *s2)
{
	char		*new_str;
	int			i;
	int			j;

	if (ft_strlen(s1) + ft_strlen(s2) > 21)
	{
		printf("string is too long\n");
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * 20);
	i = 0;
	j = 0;
	while (s1[i])
	{
		new_str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_str[j] = s2[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

static int	check_valid_pwd(int connexion, int sock)
{
	char		*phrase;
	char		*ret;

	ret = (char *)malloc(sizeof(char) * 24);
	printf("type a login (A-Z, a-z, 0-9), 10 char max\n");
	get_next_line(0, &ret);
	while(1)
	{
		if (ret == NULL)
			get_next_line(0, &ret);
		if (is_valid(ret) == 1)
		{
			printf("type a login (A-Z, a-z, 0-9), 10 char max\n");
			free(ret);
			get_next_line(0, &ret);
		}
		else
			break ;
	}
	ret = concat(ret, ":");
	printf("type a password (A-Z, a-z, 0-9), 10 char max\n");
	get_next_line(0, &phrase);
	while(1)
	{
		if (phrase == NULL)
			get_next_line(0, &phrase);
		if (is_valid(phrase) == 1)
		{
			printf("type a password (A-Z, a-z, 0-9), 10 char max\n");
			free(phrase);
			get_next_line(0, &phrase);
		}
		else
			break ;
	}
	ret = concat(ret, phrase);
	if (connexion == 1)
		ret = concat(ret, ":1");
	else
		ret = concat(ret, ":0");
	write(sock, ret, ft_strlen(ret));
	return(1);
}

static void	sign_in(int sock)
{
	char		*readed;

	printf("Wanna sign in, yes/no ?\n");
	get_next_line(0, &readed);
	if (ft_strcmp(readed, "yes") == 0)
		check_valid_pwd(0, sock);
	else if (ft_strcmp(readed, "no") == 0)
	{
		printf("U wont test my projetct\n");
		write(sock, "EXIT\n", 5);
		exit(0);
	}
	else
	{
		free(readed);
		sign_in(sock);
	}
}

static void	auth_server(int sock)
{
	char		*readed;

	printf ("on est bien dans auth\n");
	while (read(sock, &readed, 3) == 0)
	{
		if (ft_strcmp(readed, "0\n") == 0)
		{
			free(readed);
			printf("ok tout va bien signale recu 0\n");
		}
		else if (ft_strcmp(readed, "-1\n") == 0)
		{
			free(readed);
			printf("Someone has ever created this account\n");
			sign_in(sock);
		}
		else if (ft_strcmp(readed, "-2\n") == 0)
		{
			printf("Wrong password , call auth function again\n");
			free(readed);
			auth(sock);
		}
		else if (ft_strcmp(readed, "-3\n") == 0)
		{
			printf("U will be redirected on sign_in service\n");
			free(readed);
			sign_in(sock);
		}
	}
}

void		auth(int sock)
{
	char		*readed;
	int			ok;

	ok = 0;
	printf ("Are u registred yes/no?\n");
	get_next_line(0, &readed);
	while (ok == 0)
	{
		if (ft_strcmp(readed, "yes") == 0)
		{
			if (check_valid_pwd(1, sock) == 0)
			{
				printf ("Are u registred yes/no?\n");
				ok = -1;
			}
			else
				ok++;
		}
		else if (ft_strcmp(readed, "no") == 0)
			ok = -1;
		else
			printf ("Are u registred yes/no?\n");
		if (ok == 0)
			get_next_line(0, &readed);
	}
	if (ok <= -1)
		sign_in(sock);
	auth_server(sock);
}

/*void		auth(int sock)
{
	char			*rv;
	char			*phrase;
	int				ok;

	phrase = NULL;
	ok = 0;
	printf("Are u registred, yes/no?\n");
	get_next_line(0, &rv);
	while (1)
	{
		if (ft_strcmp(rv, "yes") == 0)
		{
			if (check_valid_pwd(1, sock) == 0)
			{
				printf("Are u registred, yes/no?\n");
				continue ;
			}
			else
			{
				ok = 1;
				break ;
			}
		}
		else if (ft_strcmp(rv, "no") == 0)
			break ;
		else
			printf("Are u registred, yes/no?\n");
		get_next_line(0, &rv);
	}
	if (ok != 1)
	{
	printf("Wanna sign in, yes/no ?\n");
	get_next_line(0, &phrase);
	while (1)
	{
		if (ft_strcmp(phrase, "yes") == 0)
			check_valid_pwd(0, sock);
		else if (ft_strcmp(phrase, "no") == 0)
		{
			printf("U wont test my projetct\n");
			write(sock, "EXIT\n", 5);
			exit(0);
		}
		else
			printf("Wanna sign in , yes/no\n");
		get_next_line(0, &phrase);
	}
}
	free(phrase);
printf("tanmer\n");
	while (read(sock, &phrase, 3) == 0)
	{
		if (strcmp(phrase, "-1\n") == 0)
			auth(sock);
		else if (strcmp(phrase, "0\n") == 0)
			break ;
	}
}*/
