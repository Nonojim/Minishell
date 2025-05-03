/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npederen <npederen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:48:43 by npederen          #+#    #+#             */
/*   Updated: 2025/01/27 20:04:19 by npederen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(char *stash, char	*line)
{
	ssize_t	nbytes;

	nbytes = 0;
	while (stash[nbytes] != '\n' && stash[nbytes] != '\0')
		nbytes++;
	if (stash[nbytes] == '\n')
		nbytes++;
	line = malloc((nbytes + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line[nbytes] = '\0';
	nbytes--;
	while (0 <= nbytes)
	{
		line[nbytes] = stash[nbytes];
		nbytes--;
	}
	return (line);
}

char	*init_stash(int fd, char *stash, char *buffer)
{
	ssize_t		nbytes;

	nbytes = 1;
	if (!stash)
		stash = ft_strdup("");
	while (nbytes > 0)
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nbytes] = '\0';
		stash = ft_gnl_strjoin(stash, buffer);
		if ((ft_strchr(buffer, '\n')))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_new_stash(char *stash)
{
	ssize_t		nbytes;
	char		*tmp;
	int			i;

	nbytes = 0;
	while (stash[nbytes] != '\n' && stash[nbytes] != '\0')
		nbytes++;
	if (stash[nbytes] == '\n')
		nbytes++;
	tmp = malloc((ft_strlen(stash) - nbytes + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (stash[nbytes])
	{
		tmp[i] = stash[nbytes];
		i++;
		nbytes++;
	}
	free(stash);
	tmp[i] = '\0';
	stash = tmp;
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
		return (NULL);
	}
	stash = init_stash(fd, stash, buffer);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = get_new_line (stash, line);
	stash = get_new_stash (stash);
	return (line);
}
/*int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	char* line = get_next_line(fd);
	printf("line 1: %s", line);
	free(line);
	//printf("line 2: %s", get_next_line(fd));
	//printf("line 3: %s", get_next_line(fd));
	close(fd);
	char *line;
    printf("Saisissez du texte (Ctrl+D pour terminer) :\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("Lu : %s", line);
        free(line);
    }*/
//	return (0);
//}*/