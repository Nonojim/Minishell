/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:31:41 by npederen          #+#    #+#             */
/*   Updated: 2024/12/14 15:31:41 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_hex(unsigned long n)
{
	int	total;

	total = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n > 0)
	{
		n /= 16;
		total++;
	}
	return (total);
}
