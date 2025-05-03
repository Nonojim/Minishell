/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:39:33 by npederen          #+#    #+#             */
/*   Updated: 2024/12/13 20:40:50 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_picker(char c, va_list arg)
{
	if (c == 'c')
		return (ft_display_c(arg));
	if (c == 's')
		return (ft_display_s(arg));
	if (c == '%')
		return (ft_display_psign());
	if (c == 'd' || c == 'i')
		return (ft_display_i(arg));
	if (c == 'u')
		return (ft_display_u(arg));
	if (c == 'x' || c == 'X')
		return (ft_display_x(arg, c));
	if (c == 'p')
		return (ft_display_p(arg));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		length;
	char	c;

	va_start(arg, str);
	length = 0;
	while (*str)
	{
		c = *str++;
		if (c != '%')
		{
			ft_putchar_fd(c, 1);
			length++;
		}
		else if (*str)
		{
			c = *str++;
			length += ft_display_picker(c, arg);
		}
	}
	va_end(arg);
	return (length);
}

/*int	main (void)
{
	void *testnull = NULL;
	int x = 42;
	int *ptr = &x;
	char *str = NULL;
	int	result = 
	ft_printf("%p et %p et %x%u et la %%%%lettre %s et %c", 
	ptr, testnull, 255, 4, str, 'x');
	printf("%d", result);
	return (0);
}*/
