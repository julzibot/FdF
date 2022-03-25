/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:20:05 by jibot             #+#    #+#             */
/*   Updated: 2022/03/25 16:18:30 by jibot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	is_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (i);
	else
		return (0);
}

int	get_save(char *buffer, char *save)
{
	int			i;
	static int	flag;

	i = 0;
	if (!save && flag != 0)
		return (-1);
	else if (!save && flag == 0)
	{
		return (0);
		flag++;
	}
	while (save[i])
	{
		buffer[i] = save[i];
		i++;
	}
	return (i);
}

char	*get_full_line(char *line, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		nbyte;

	while (!is_line(line))
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		nbyte = read(fd, buffer, BUFFER_SIZE);
		if (nbyte == 0)
			return (line);
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

char	*line_cut(char *line, char *buffer)
{
	int	i;
	int	blen;

	i = is_line(line);
	blen = get_strlen(line);
	if ((i && line[blen - 1] != '\n') || (buffer[0] == '\n' && blen > 1)
		|| (line[blen - 1] == '\n' && i < blen - 1 && blen > 1))
		line[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*save;
	char		*line;
	int			i;
	int			blen;

	i = get_save(buffer, save);
	ft_bzero(buffer + i, BUFFER_SIZE - i + 1);
	blen = read(fd, buffer + i, BUFFER_SIZE - i);
	if ((i == -1 && blen < 0) || !buffer[0] || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	else if (is_line(buffer) > 0 || buffer[0] == '\n')
		line = ft_strdup(buffer);
	else
		line = get_full_line(ft_strdup(buffer), fd);
	free(save);
	i = is_line(line);
	blen = get_strlen(line);
	if ((i && line[blen - 1] != '\n') || (buffer[0] == '\n' && blen > 1)
		|| (line[blen - 1] == '\n' && i < blen - 1 && blen > 1))
		save = ft_strdup(line + i + 1);
	else
		save = NULL;
	line = line_cut(line, buffer);
	return (line);
}

/*int	main(void)
{
	int	fd = open("testdoc.txt", O_RDONLY);
	//int	fd = open("3char.txt", O_RDONLY);
	//int	fd = open("BUFFER_SIZEnl.txt", O_RDONLY);
	//int	fd = open("41_no_nl.txt", O_RDONLY);
	//int	fd = open("41_with_nl.txt", O_RDONLY);
	int i = 0;
	char	*line;

	while (i++ < 20)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	free(line);
	//close(fd);
}*/
