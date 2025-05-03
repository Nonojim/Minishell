/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:07:41 by npederen          #+#    #+#             */
/*   Updated: 2024/12/14 15:07:41 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hex_fd(unsigned long n, int upper, int fd)
{
	char	*str;
	char	c;

	if (upper)
		str = "0123456789ABCDEF";
	else
		str = "0123456789abcdef";
	if (n >= 16)
		ft_putnbr_hex_fd(n / 16, upper, fd);
	c = str[n % 16];
	write(fd, &c, 1);
}
