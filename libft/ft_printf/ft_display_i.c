/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:04:44 by npederen          #+#    #+#             */
/*   Updated: 2024/12/16 17:04:44 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_display_i(va_list arg)
{
	int	value;

	value = va_arg(arg, int);
	ft_putnbr_fd(value, 1);
	return (ft_count(value));
}
