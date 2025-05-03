/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:04:47 by npederen          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:47 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_c(va_list arg)
{
	char	c;

	c = (char)va_arg(arg, int);
	ft_putchar_fd(c, 1);
	return (1);
}
