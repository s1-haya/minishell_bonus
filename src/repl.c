/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:35:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/24 19:18:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

static void	add_line_history(char *line)
{
	if (line[0] == NULL_CHAR)
		return ;
	add_history(line);
}

static char	*read_line()
{
	char	*line;

	line = readline(PROMPT);
	if (!line)
		return (NULL);
	add_line_history(line);
	return (line);
}

void	read_eval_print_loop()
{
	char	*line;

	while (true)
	{
		line = read_line();
		if (line == NULL)
			break ;
		// printf("line          %s\n", line);
		printf("start 0 end 3 %s\n", ft_substr(line, -1, 3));
		printf("start 2 end 7 %s\n", ft_substr(line, 2, 7));
		free(line);
	}
}
