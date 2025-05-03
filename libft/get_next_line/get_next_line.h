/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:48:22 by npederen          #+#    #+#             */
/*   Updated: 2025/01/14 16:48:22 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*ft_gnl_strjoin(char *s1, const char *s2);

#endif