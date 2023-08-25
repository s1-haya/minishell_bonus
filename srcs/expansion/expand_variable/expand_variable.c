/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/26 00:10:51 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_variable_word(char *word)
{
	t_quote	f_quote;
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		f_quote = token_set_flag_quote(word[i]);
		if (f_quote == SINGLE_QUOTE_FLAG)
		{
			while (f_quote != token_set_flag_quote(word[++i]))
			{
				if (word[i] == '\0')
					return (false);
			}
			i++;
		}
		else
		{
			if (word[i] == '$')
				return (true);
			i++;
		}
	}
	return (false);
}

void	expand_variable_word_list(t_word_list *word_list, t_data *d)
{
	char	*expand_word;

	if (expand_is_variable_word(word_list->word))
	{
		
		// printf("word     %s\n", word_list->word);
		expand_word = expand_get_expanded_token(word_list->word, d);
		// printf("expand   %s\n", expand_word);
		word_list->word = expand_word;
	}
}

void	expand_variable_redirect_list(t_redirect_list *redirect_list, t_data *d)
{
	char	*expand_word;

	if (expand_is_variable_word(redirect_list->word))
	{
		
		// printf("word     %s\n", redirect_list->word);
		expand_word = expand_get_expanded_token(redirect_list->word, d);
		// printf("expand   %s\n", expand_word);
		redirect_list->word = expand_word;
	}
}
