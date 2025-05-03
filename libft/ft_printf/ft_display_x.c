/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:04:31 by npederen          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:31 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_x(va_list arg, char c)
{
	unsigned int	value;
	int				upper;

	value = va_arg(arg, unsigned int);
	upper = (c == 'X');
	ft_putnbr_hex_fd(value, upper, 1);
	return (ft_count_hex(value));
}
