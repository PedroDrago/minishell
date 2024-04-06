#include "../includes/minishell.h"
#include <stdio.h>

// void	resolve_error(int status, char *command)
// {
// 	//40192 file not found (redirections)
// 	//39936 no permission for file (redirections)
// 	if (status == 2) //FIX: Is this necessary? if something about signals breaks, this is the reasong. resolve_error was used in wait_children
// 		g_sig = SIGINT;
// }
