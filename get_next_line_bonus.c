/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:11:17 by veragarc          #+#    #+#             */
/*   Updated: 2024/10/11 12:11:21 by veragarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (stash == NULL)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(stash, '\n') != NULL)
			break ;
	}
	return (stash);
}

static char	*set_line(char *line_buffer)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
	{
		if (line_buffer[i] == '\n')
			break ;
		else
			i++;
	}
	stash = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*stash == 0)
	{
		free(stash);
		return (NULL);
	}
	line_buffer[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash[fd]);
		free(buffer);
		return (NULL);
	}
	if (buffer == NULL)
		return (NULL);
	line = fill_line_buffer(fd, stash[fd], buffer);
	free (buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	stash[fd] = set_line(line);
	return (line);
}

/* int	main(void)
{
    char*	fileName = "hello.txt";
    int		fd1;
    int		fd2;
    int		fd3;
    char*	line;

    fd1 = open(fileName, O_RDWR);
    fd2 = open("hola.txt", O_RDWR);
    fd3 = open("adios.txt", O_RDWR);
    line = get_next_line(fd1);
    printf("1: %s", line);
    line = get_next_line(fd2);
    printf("2: %s", line);
    line = get_next_line(fd3);
    printf("3: %s", line);
    return (0);
} */

/* int	main(void)
{
    char*	fileName = "hello.txt";
    int		fd;
    int		fd2;
    int		fd3;
    char*	line;

    fd = open(fileName, O_RDWR);
    fd2 = open("hola.txt", O_RDWR);
    fd3 = open("adios.txt", O_RDWR);
    line = (char *) 1;
    if (fd == -1)
    {
        printf("Error openning file\n");
        return (-1);
    }
    while (line)
    {
        line = get_next_line(fd);
        if (line)
        {	
            printf("Resultado: %s", line);
            free(line);
        }
        line = get_next_line(fd2);
        printf("2: %s\n", line);
        line = get_next_line(fd3);
        printf("3: %s\n", line);
    }
    return (0);
} */
