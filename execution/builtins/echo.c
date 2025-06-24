/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:55:08 by lduflot           #+#    #+#             */
/*   Updated: 2025/06/24 18:26:47 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* echo ouaf = 
*ouaf \n

* echo -n ouaf =
* ouaf%
*
* echo -nnnnnnnnnnnnnnnnnnnnnnnn ouaf =
* ouaf%
*/



int	parse_cmd(char *cmd, int *error)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd, "test") == 0)
		return (0);
	else if (*error == 0)
	{
		printf("%s: command not found\n", cmd);
		*error = 1;
		return (1);
	}
	return (1);
}
