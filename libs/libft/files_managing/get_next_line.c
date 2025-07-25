/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:42:49 by vdurand           #+#    #+#             */
/*   Updated: 2025/07/16 12:14:52 by halnuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static size_t	bufcpy(char *dest, const char *src)
{
	size_t	index;

	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	while (index < GNL_BUFFER_SIZE)
	{
		dest[index] = '\0';
		index++;
	}
	dest[index] = '\0';
	return (index);
}

static size_t	iuntilchar(char *str, char c)
{
	size_t	index;

	index = 0;
	while (str[index] && str[index] != c)
		index++;
	if (str[index] == c)
		index++;
	return (index);
}

char	*ft_join_nline(char *s1, char *s2)
{
	char	*result;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (s1 == NULL)
		{
			return (NULL);
		}
		s1[0] = '\0';
	}
	result = ft_strjoin(s1, s2);
	if (ft_strchr(s2, '\n') == NULL)
		ft_bzero(s2, ft_strlen(s2));
	free(s1);
	if (!result)
		return (NULL);
	return (result);
}

static t_gnl_result	gnl_return(char *line, int error, int ended, bool dofree)
{
	t_gnl_result	result;

	result.line = line;
	result.ended = ended;
	if (dofree)
	{
		free(result.line);
		result.line = NULL;
	}
	result.error = error;
	return (result);
}

t_gnl_result	get_next_line(int fd)
{
	static char		buffer[GNL_BUFFER_SIZE + 1];
	ssize_t			readed;
	char			*line;
	char			*res;

	line = NULL;
	while (ft_strchr(line, '\n') == NULL)
	{
		if (buffer[0] == '\0')
		{
			readed = read(fd, buffer, GNL_BUFFER_SIZE);
			if (readed == -1)
				return (gnl_return(line, 1, 0, true));
			if (readed == 0)
				return (gnl_return(line, 0, 1, false));
		}
		line = ft_join_nline(line, buffer);
		if (!line)
			return (gnl_return(NULL, 1, 0, false));
	}
	res = ft_substr(line, 0, iuntilchar(line, '\n'));
	free(line);
	if (res)
		bufcpy(buffer, buffer + iuntilchar(buffer, '\n'));
	return (gnl_return(res, res == NULL, 0, false));
}

/*  int	main(void)
 {
 	int fd = open("1char.txt", O_RDONLY);
 	char *test;
 	test = get_next_line(fd);
 	printf("line = '%s'\n", test);
 	free(test);
 	while (test != NULL)
 	{
 		test = get_next_line(fd);
 		printf("line = '%s'\n", test);
 		free(test);
 	}
 	close(fd);
 }  */