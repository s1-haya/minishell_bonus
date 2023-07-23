/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:43:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/23 17:39:28 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define NULL_CHAR ('\0')
#define PROMPT ("minishell$ ")
// t_token	*tokenize(const char *line);
void	read_eval_print_loop();
#endif