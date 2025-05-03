/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:32:48 by npederen          #+#    #+#             */
/*   Updated: 2024/12/14 17:32:48 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "../libft.h"

int		ft_printf(const char *str, ...);
int		ft_count(long n);
int		ft_count_unsigned(unsigned long n);
int		ft_count_hex(unsigned long n);
void	ft_putnbr_unsigned_fd(unsigned long n, int fd);
void	ft_putnbr_hex_fd(unsigned long n, int upper, int fd);
int		ft_display_psign(void);
int		ft_display_c(va_list arg);
int		ft_display_s(va_list arg);
int		ft_display_i(va_list arg);
int		ft_display_u(va_list arg);
int		ft_display_p(va_list arg);
int		ft_display_x(va_list arg, char c);

#endif
