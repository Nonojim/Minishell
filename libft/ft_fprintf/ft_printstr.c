/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:51:05 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 19:45:53 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *str, int fd)
{
	int	count;

	count = 0;
	if (str == NULL)
	{
		write(fd, "(null)", 6);
		count = count + 6;
		return (count);
	}
	while (str[count] != '\0')
	{
		ft_printchar(str[count], fd);
		count++;
	}
	return (count);
}
