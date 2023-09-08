/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:36:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/08 17:04:34 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*get_type_str_to_dollar(char *expand_word, char **type)
{
	char	*new_type;
	size_t	i;

	new_type = try_calloc(ft_strlen(expand_word) + 1, sizeof(char));
	i = 0;
	while (expand_word[i] != '\0')
	{
		// if (*(*type) == '0')
		// 	new_type[i] = '1';
		// else
		new_type[i] = *(*type);
		(*type)++;
		i++;
	}
	return (new_type);
}

void	expand_get_joined_str(char **join_word,
						char **join_type,
						char *expand_word)
{
	char	*type;

	// printf("expand %s\n", *join_type);
	type = token_get_type_word(expand_word, true);
	printf("expand %s\n", type);
	*join_word = try_strjoin_free(*join_word, expand_word);
	*join_type = try_strjoin_free(*join_type, type);
	free(type);
}

void	expand_get_joined_str_to_dollar(char **join_word,
									char **join_type,
									char **tmp,
									char **tmp_type)
{
	char	*expand_word;
	char	*type;

	expand_word = expand_get_str_to_dollar(tmp, *tmp_type);
	printf("join_word %s\n", *join_word);
	printf("join_type %s\n", *join_type);
	printf("word      %s\n", expand_word);
	type = get_type_str_to_dollar(expand_word, tmp_type);
	printf("type      %s\n", type);
	*join_word = try_strjoin_free(*join_word, expand_word);
	*join_type = try_strjoin_free(*join_type, type);
	free(expand_word);
	free(type);
}
