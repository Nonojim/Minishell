/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lduflot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:53:11 by lduflot           #+#    #+#             */
/*   Updated: 2025/07/16 19:53:04 by lduflot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "../libft.h"

int		ft_fprintf(int fd, const char *type, ...);
int		ft_printhexamaj(int nb, int fd);
int		ft_printadress(void *adress, int fd);
int		ft_printhexaminus(int nb, int fd);
int		ft_printnbr(int nb, int fd);
int		ft_printchar(char c, int fd);
int		ft_printstr(char *str, int fd);
int		ft_printnbrunsigned(int nb, int fd);

#endif
