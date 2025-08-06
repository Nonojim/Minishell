/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:34:06 by npederen          #+#    #+#             */
/*   Updated: 2025/08/06 16:20:45 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (uc >= 128)
		return (1);
	if (uc >= 32 && uc <= 126)
		return (1);
	return (0);
}
