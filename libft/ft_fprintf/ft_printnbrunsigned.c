/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbrunsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:03:33 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 19:45:39 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbrunsigned(int nb, int fd)
{
	unsigned int	n;
	int				count;

	count = 0;
	n = nb;
	if (n <= 9)
		count = count + ft_printchar(n + '0', fd);
	else
	{
		count = count + ft_printnbr(n / 10, fd);
		count = count + ft_printnbr(n % 10, fd);
	}
	return (count);
}
