/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:04:34 by npederen          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:34 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_u(va_list arg)
{
	unsigned int	value;

	value = va_arg(arg, unsigned int);
	ft_putnbr_unsigned_fd(value, 1);
	return (ft_count_unsigned(value));
}
