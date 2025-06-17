/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <lduflot@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:05:41 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/17 19:18:22 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/*
Cas gerer dans l expansion:
$EXPANSION
Simple et double quote 
*
*/
void	expanse_ast()
{
	const char	*home = "HOME";
	const char	*var = "PATH";
	const char	*date = "(DATE)";
	const	char	*user = "USER";
	const char	*env_p = getenv(home);
	
	const char	*env_p1 = getenv(var);
	const char	*env_p2 = getenv(date);
	const char	*env_p3 = getenv(user);
	if (env_p)
  	printf("HOME: %s\n", env_p);
	if (env_p)
  	printf("PATH: %s\n", env_p1);
	if (env_p)
  	printf("DATE: %s\n", env_p2);
	if (env_p)
  	printf("USER: %s\n", env_p3);

}
// Si expansion mis sans commande associe erreur :
/*HOME = bash: /home/lduflot: Is a directory
PATH = bash: /home/lduflot/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/lduflot/.local/bin:/home/zephyre/.local/bin:/home/zephyre/.venv/bin: No such file or directory
USER = lduflot: command not found
*/

/*char	*getcwd(char *buf, size_t size)
->recupere chemin absolu du rep courant 

char *getenv(const char *name)
->recupere la valeur d une var d env
*/

