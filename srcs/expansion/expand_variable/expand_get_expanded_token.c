/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_expanded_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:02:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/26 16:13:33 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char *expand_get_expand_word(char **word, t_envs **envs)
{
	char *target_word;
	char *target_value;

	target_word = expand_get_string_to_dollar_or_symbol(word);
	target_value = envs_get_value(target_word, envs);
	return (target_value);
}

char *expand_convert_dollar_word(char **word, t_data *d)
{
	char *expand_word;
	t_quote f_quote;

	expand_word = *word;
	(*word)++;
	f_quote = token_set_flag_quote((*word)[0]);
	if (**word == '\0')
		return (try_strdup(expand_word));
	if (f_quote == SINGLE_QUOTE_FLAG || f_quote == DOUBLE_QUOTE_FLAG)
		expand_word = expand_get_delete_dollar_quote(word, f_quote, d);
	else if (**word == '?')
		expand_word = expand_get_exit_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	// printf("expand %s\n", expand_word);
	return (expand_word);
}

// typeを作る　voidにしてchar *token, char *typeにポインタ文字列入れる

void	expand_get_expanded_token(char **token, char **type, t_data *d)
{
	char	*tmp;
	char	*expand_word;
	char	*join_word;
	char	*join_type_word;

	join_word = NULL;
	join_type_word = NULL;
	tmp = *token;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			expand_word = expand_convert_dollar_word(&tmp, d);
			join_word = try_strjoin_free(join_word, expand_word);
			join_type_word = try_strjoin_free(join_type_word, token_get_type_word(expand_word, true));
			free(expand_word);
		}
		else
		{
			expand_word = expand_get_str_to_dollar(&tmp);
			join_word = try_strjoin_free(join_word, expand_word);
			join_type_word = try_strjoin_free(join_type_word, token_get_type_word(expand_word, false));
			free(expand_word);
		}
	}
	// printf("word     %s\n", join_word);
	*token = join_word;
	*type = join_type_word;
}

// int main(void)
// {
// 	extern const char **environ;
// 	t_data data;
// 	//環境変数展開
// 	//環境変数がない場合
// 	// - "$B" \0
// 	// - $B NULL

// 	data.exit_status = 0;
// 	envs_init(environ, &data);
// 	//末尾に空白を入れたらokになる
// 	debug_printf_test(NULL, expand_get_expanded_token("$B", &data));
// 	debug_printf_test("?llll", expand_get_expanded_token("?llll", &data));
// 	debug_printf_test("?llll", expand_get_expanded_token("$ABV?llll", &data));
// 	debug_printf_test("B+++", expand_get_expanded_token("$A+++$B", &data));
// 	debug_printf_test("echo     B", expand_get_expanded_token("echo   $D  $A", &data));
// 	debug_printf_test("B", expand_get_expanded_token("$B$A", &data));
// 	debug_printf_test("sawamurashunsawamurashun", expand_get_expanded_token("$USER$USER", &data));
// 	debug_printf_test("/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/opt/X11/bin:/opt/homebrew/bin:/opt/homebrew/sbin", expand_get_expanded_token("$BD$PATH", &data));
// 	// printf("output   %s\n", expand_get_expanded_token("$B$A$", &data));
// 	// printf("output   %s\n", expand_get_expanded_token("$B$A", &data));
// 	// printf("output   %s\n", expand_get_expanded_token("$B$A", &data));
// 	return (0);
// }
