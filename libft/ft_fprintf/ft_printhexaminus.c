/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexaminus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:52:40 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 19:45:04 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////////////////////////////////////////////////
//En hexadecimal il y a 16 chiffres, 0 a 9 puis de 10 a 15 
//avantage= format compact, abreger ecriture binaire, facilite manipulation
//10=A 11=B 12=C 13=D 14=E 15=F 16=10 17=11
//nb / 16 = quotient entier
//nb - (quotient entier * 16) = reste 
//ex = 75/16 = 4 ; 75 -(4*16) = 11 = 4B (car b = 11)
/////////////////////////////////////////////////////////////////////////////
/**
	* @brief description de la fontion
	* @params exemple: nb signifie le nombre donne en parametre
	* @return example: return an in who's the number of bytes writed.
	* etc. lolol kiss kiss xoxo 
	*/

#include "ft_printf.h"

/*long long int	ft_complement2(long long int n);

void	ft_printbinaire(long long int n)
{
	if (n > 1)
	{
		ft_printbinaire(n / 2);
	}
	ft_printhexaminus(n % 2 + '0');
}

long long int ft_complement2(long long int n)
{
	unsigned long long int nb = (long long int)n;
	
	if (nb > 1)
	{
		ft_complement2(nb / 2);
	}
	ft_printchar(nb % 2 + '0');

	if (nb == 0)
		nb = 1;
	else if (nb == 1)
		nb = 0;
	return (nb);
}

long long int	ft_addone(long long int n)
{
	n = n + 1;
	return (n);
}
*/
int	ft_printlettre(long long int nb, int fd)
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

int	ft_printhexaminus(int nb, int fd)
{
	int				count;
	unsigned int	n;

	count = 0;
	n = (unsigned int) nb;
	if (n == 0)
	{
		write(fd, "0", 1);
		count = 1;
		return (count);
	}
	if (n > 0 && n <= 9)
		count = count + ft_printchar(n + '0', fd);
	else if (n >= 10 && n <= 15)
		count = count + ft_printlettre(n, fd);
	else if (n >= 16)
	{
		count = count + ft_printhexaminus(n / 16, fd);
		count = count + ft_printhexaminus(n % 16, fd);
	}
	return (count);
}

/*#include <stdio.h>

int	main(void)
{
	//int test1 = -255;
	long long int test = -255;
	int test2 = 255;

	ft_printhexaminus(test);
	printf("\ntest neg:%llX\n", (long long int)test);
	printf("test pos:%X\n", test2);
	return (0);
}*/
