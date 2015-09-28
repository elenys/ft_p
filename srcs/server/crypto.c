#include <stdio.h>
#include <stdlib.h>
#include "libft.h"


static char	rot_13(char c)
{
	if (c >= 'z' - 13)
		return (c - 'z' + 48);
	return (c + 13);
}

char		*crypto(char *str)
{
	int			i;
	char		*new_str;

	new_str = (char *)malloc(sizeof(char) * ft_strlen(str) + 5);
	i = 0;
	while (str[i])
	{
		new_str[i] = rot_13(str[i]);
		i++;
	}
	new_str[i++] = 'M';
	new_str[i++] = 'c';
	new_str[i++] = 'D';
	new_str[i++] = 'O';
	new_str[i] = '\0';
	return (new_str);
}