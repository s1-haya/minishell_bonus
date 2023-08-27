/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:59 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/27 23:02:40 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#define HEREDOC_PROMPT "> "

static void	all_free(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

char	*heredoc_read(t_data *d)
{
	char	buff[BUFFER_SIZE + 1];
	char	*line;
	ssize_t	read_bytes;

	line = NULL;
	try_write(STDERR_FILENO, "> ", ft_strlen(HEREDOC_PROMPT), d);
	read_bytes = BUFFER_SIZE + 1;
	while (read_bytes > BUFFER_SIZE)
	{
		read_bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
			return (NULL);
		buff[read_bytes] = '\0';
		if (line == NULL)
			line = try_strdup(buff);
		else
			line = try_strjoin_free(line, buff);
	}
	return (line);
}

bool	heredoc_read_loop(t_redirect_list *delimiter, t_data *d)
{
	char	*str;
	char	*buff;
	char	*check;

	str = try_strdup("");
	check = try_strjoin(delimiter->word, "\n");
	while (true)
	{
		buff = heredoc_read(d);
		if (buff == NULL)
		{
			all_free(buff, delimiter->word, check);
			delimiter->word = str;
			return (false);
		}
		if (ft_strcmp(buff, check) == 0)
		{
			all_free(buff, delimiter->word, check);
			delimiter->word = str;
			break ;
		}
		str = try_strjoin_free(str, buff);
	}
	return (true);
}
