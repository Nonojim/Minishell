/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:00:35 by npederen          #+#    #+#             */
/*   Updated: 2024/12/14 16:00:35 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_unsigned(unsigned long n)
{
	int	total;

	total = 0;
	if (n == 0)
	{
		return (1);
	}
	while (n > 0)
	{
		n /= 10;
		total++;
	}
	return (total);
}
