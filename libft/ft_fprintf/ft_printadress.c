/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printadress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:57:21 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 19:42:28 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

//Adresse du pointeur =
// %p
// prefixe 0x (indique que les valeurs apres sont ecritent en hexadecimal 
// &

int	ft_print(long long int nb, int fd)
{
	if (nb == 10)
		return (ft_printchar('a', fd));
	if (nb == 11)
		return (ft_printchar('b', fd));
	if (nb == 12)
		return (ft_printchar('c', fd));
	if (nb == 13)
		return (ft_printchar('d', fd));
	if (nb == 14)
		return (ft_printchar('e', fd));
	if (nb == 15)
		return (ft_printchar('f', fd));
	return (0);
}

int	ft_printhexa(unsigned long nb, int fd)
{
	int				count;

	count = 0;
	if (nb <= 9)
		count = count + ft_printchar(nb + '0', fd);
	else if (nb >= 10 && nb <= 15)
		count = count + ft_print(nb, fd);
	else if (nb >= 16)
	{
		count = count + ft_printhexa(nb / 16, fd);
		count = count + ft_printhexa(nb % 16, fd);
	}
	return (count);
}

int	ft_printadress(void	*adress, int fd)
{
	unsigned long int	p;
	int					count;

	p = (unsigned long)adress;
	count = 0;
	if (adress == NULL)
		count = count + write(fd, "(nil)", 5);
	else
	{
		count = count + write(fd, "0x", 2);
		count = count + ft_printhexa(p, fd);
	}
	return (count);
}

/*#include <stdio.h>

int	main(void)
{
	char *test = "ckefz";

	ft_printadress((char *)test);
}*/
