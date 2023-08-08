/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/06 21:50:35 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "ft.h"
# include "init.h"
# include "tokenize.h"

typedef enum e_redirect_type
{
	REDIRECTING_INPUT, // <
	REDIRECTING_OUTPUT,// >
	APPENDING_OUTPUT,// >>
	FILE,// redirect fil
	HERE_DOCUMENTS, // <<
	DELIMITER, // << delimitter(クウォートがない場合)
	QUOTE_DELIMITER, // << delimitter(クウォートがある場合)
}	t_redirect_type;

typedef enum e_ast_node_type
{
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
	COMMAND,
}	t_ast_node_type;

typedef struct s_word_list
{
	char				*word;
	size_t				index;//クォートが閉じるまで更新されない
	t_token_type		type;
	struct s_word_list	*next;
}	t_word_list;

typedef struct s_redirect
{
	char				*word;
	size_t				index;
	t_redirect_type		type;
	bool 	is_ambiguas_error;//初期値はfalse
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	t_word_list	*word_list;
	t_redirect	*redirect_list;
	int			fd;//どこにコマンドを出力するか(初期値はSTD OUT FILNE NO)
	pid_t		pid;//子プロセスのIDを管理(初期値は-1)
}	t_command;

typedef struct s_ast
{
	t_ast_node_type		type;
	struct s_command	*command_list;
	struct s_ast		*left_hand;
	struct s_ast		*right_hand;
}	t_ast;


//t_ast関連
t_ast *ast_parse(t_token **token_address, t_data *d);
t_ast *ast_command(t_token *token,t_data *d);
t_ast *ast_make_command_list(t_ast *node,t_token **token);
t_ast *ast_make_ast_ope(e_ast_node_type,t_ast *left_hand,t_ast *right_hand);
t_ast *ast_init_node(t_token **token_adress)
void ast_add_back_ast_node(t_ast **head, t_ast *new_node);

//t_command関連
void ast_make_word_list(t_command command_list, t_token token);
void ast_make_redirect_list(t_redirect redirect_list, t_token **token_address,t_data *d);

//t_word_list関連
t_word_list *ast_init_word_node(t_word *word);
void *ast_add_back_word_list(t_word **head,t_word *node);

//t_redirect関連
t_redirect *ast_init_redirect_node(t_redirect *node);
void *ast_add_back_redirect_list(t_redirect **head,t_redirect *node);

//error関連
bool is_operator(e_ast_node_type type);
bool is_quotation_closed(t_token *token_adress);
void ast_expect(t_token **token,char op);
t_token	*ast_token_next(t_token **token_address);
void ast_free_all_nodes(t_ast *node);
void * syntax_error(t_ast *left_node,t_ast *right_node)

/* void* try_calloc(size_t nmemb,size_t size); */

ls infileC a b | ls

ls infile a b << eof <Makefile > out >> apend | ls a b c d

1 ls 2 infile 3> 4a 5b 6<< 7eof <Makefile | ls
1ls 2infile 5b 
3> 4a << eof <Makefile

cat
infiile
|
ls

------------------------

cmd1 | cmd2 || cmd3 | cmd4

				|
			||		cmd4
		|		cmd3
	cmd1	cmd2
------------------------

cmd1 | (cmd2 || cmd3) | cmd4

		|
	cmd1	|
		||	   cmd4
	cmd2  cmd3
------------------------

------------------------
(a || b) && ls

		&&
	||		ls
a		b
------------------------


					|
				|		command4
		  |			comamnd3
command1	command2


		  |			comamnd3
command1	command2


		  |
command1	command2

<infile


		  |
command1	command2
					comamnd3
						command4

#endif
