/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:04:40 by npederen          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:40 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_p(va_list arg)
{
	void			*ptr;
	unsigned long	value;

	ptr = va_arg(arg, void *);
	value = (unsigned long)ptr;
	if (value == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_hex_fd(value, 0, 1);
		return (ft_count_hex(value) + 2);
	}
}
