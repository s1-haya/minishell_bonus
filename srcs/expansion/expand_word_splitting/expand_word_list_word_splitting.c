/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_list_word_splitting.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 23:22:43 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 09:51:01 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "library.h"

t_word_list	*expand_new_word_list(t_word_list *node, size_t i, \
									t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	i++;
	new_word_list->word = try_strdup(&(node->word[i]));
	new_word_list->type = try_strdup(&(node->type[i]));
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	return (new_word_list);
}

t_word_list	*expand_new_null_word_list(t_word_list *next_node)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = try_strdup("");
	new_word_list->type = NULL;
	new_word_list->tk_type = WORD;
	new_word_list->next = next_node;
	return (new_word_list);
}

static void	expand_can_get_word_splitting_word_list(t_word_list *word_list, \
													char *ifs, size_t i)
{
	char	*ifs_default_char;

	ifs_default_char = expand_check_ifs_default_char(ifs);
	if (i == 0)
	{
		while (word_list->word[i] != '\0' && \
				!expand_is_str_in_char(ifs, word_list->word[i]))
		{
			if (!expand_is_str_in_char(ifs_default_char, word_list->word[i]))
				word_list->next = expand_new_null_word_list(word_list->next);
			i++;
		}
	}
	else
	{
		word_list->next = expand_new_word_list(word_list, i, word_list->next);
		word_list->word = try_substr(word_list->word, 0, i);
		word_list->type = try_substr(word_list->type, 0, i);
	}
}

void	expand_word_splitting_word_list(t_word_list *node, char *ifs)
{
	t_word_list	*word_list;
	size_t		i;

	i = 0;
	word_list = node;
	while (word_list->word[i] != '\0')
	{
		if (expand_is_str_in_char(ifs, word_list->word[i]) && \
			!expand_is_quoted(word_list->type, i) && word_list->type[i] == '1')
		{
			expand_can_get_word_splitting_word_list(word_list, ifs, i);
			break ;
		}
		i++;
	}
	if (expand_have_ifs(word_list->next->word, ifs))
		expand_word_splitting_word_list(word_list->next, ifs);
}