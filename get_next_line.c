/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veragarc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:09:25 by veragarc          #+#    #+#             */
/*   Updated: 2024/10/11 12:09:28 by veragarc         ###   ########.fr       */
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
	static char	*stash;
	char		*buffer;
	char		*line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		free(buffer);
		return (NULL);
	}
	if (buffer == NULL)
		return (NULL);
	line = fill_line_buffer(fd, stash, buffer);
	free (buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	stash = set_line(line);
	return (line);
}

/* int	main(void)
{
    char*	fileName = "hola.txt";
    int		fd;
    char*	line;

    fd = open(fileName, O_RDWR);
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
    }
    return (0);
} */
