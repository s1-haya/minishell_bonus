/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:48:29 by tterao            #+#    #+#             */
/*   Updated: 2023/08/24 18:36:49 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include <stdlib.h>

size_t	exec_get_size_arr_word_list(t_word_list *word_list)
{
	size_t		size;
	t_word_list	*node;

	size = 0;
	node = word_list;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}

// char	*exec_get_word_index(t_word_list **word_list)
// {
// 	char	*word;
// 	size_t	index;

// 	index = (*word_list)->index;
// 	word = try_strdup((*word_list)->word);
// 	(*word_list) = (*word_list)->next;
// 	while ((*word_list) != NULL && index == (*word_list)->index)
// 	{
// 		word = try_strjoin_free(word, (*word_list)->word);
// 		(*word_list) = (*word_list)->next;
// 	}
// 	return (word);
// }

/**
 * @brief この関数はコマンド実行の二次元配列（argv）を作成する。
 *
 * node->command_list->word_listからコマンドを作成する。
 *
 * @param node 構文木のnode
 * @return char** コマンド実行の二次元配列（argv）
 */
char	**exec_make_argv(t_ast *node)
{
	char		**arr;
	t_word_list	*w_node;
	size_t		index;
	size_t		size;

	w_node = node->command_list->word_list;
	size = exec_get_size_arr_word_list(w_node);
	if (size == 0)
		return (NULL);
	arr = try_calloc(size + 1, sizeof(char *));
	index = 0;
	while (index < size)
	{
		arr[index] = w_node->word;
		w_node = w_node->next;
		index++;
	}
	return (arr);
}

#include <stdio.h>
void	exec_child_process(t_ast *node, int *pipefd, t_data *d)
{
	char	**argv;
	char	*filepath;
	int	fd;

	(void)pipefd;
	// printf("argv=%s--\n", node->command_list->word_list->word);
	fd = node->command_list->fd;
	if (fd != STDOUT_FILENO)
	{
		try_dup2(fd, STDOUT_FILENO, 0);
		try_close(fd, d);
	}
	if (node->command_list->word_list != NULL)
	{
		argv = exec_make_argv(node);
		// printf("argv=%s--\n", node->command_list->word_list->word);
		filepath = exec_make_filepath(node, d);
		char **tmp = argv;
		// while (*tmp)
		// {
			// printf("argv=%s\n", *tmp);
		// 	tmp++;
		// }
		// printf("path=%s\n", filepath);
		execve(filepath, argv, envs_make_envp(d->envs_hashmap));
		// execve(NULL, NULL, envs_make_envp(d->envs_hashmap));
	}
	exit(1);
}