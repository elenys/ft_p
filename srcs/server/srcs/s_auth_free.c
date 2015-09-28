#include "serveur.h"


void	free_auth_struct(t_auth auth)
{
	free(auth.user);
	free(auth.pwd);
}
