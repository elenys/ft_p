#include "ftp.h"

void	free_2d_tab(void **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(&tab[i++]);
	free(tab);
}
