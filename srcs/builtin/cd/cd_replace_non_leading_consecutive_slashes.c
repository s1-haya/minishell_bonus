/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_replace_non_leading_consecutive_slashes.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:59:00 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 20:06:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>

static char	*get_first_target_slashes(char *path)
{
	char		*cons_slash;
	const char	*dsl = "//";

	cons_slash = ft_strstr(path, dsl);
	if (path != cons_slash)
		return (cons_slash);
	while (*cons_slash != '\0')
	{
		if (*cons_slash != '/')
			break ;
		cons_slash++;
	}
	cons_slash = ft_strstr(cons_slash, dsl);
	return (cons_slash);
}

static char	*get_end_slashes(char *start)
{
	while (*start != '\0')
	{
		if (*start != '/')
		{
			start--;
			break ;
		}
		start++;
	}
	return (start);
}

char	*cd_replace_non_leading_consecutive_slashes(char *path)
{
	char	*newpath;
	char	*cons_slash;
	char	*end_slash;

	cons_slash = get_first_target_slashes(path);
	if (cons_slash == NULL)
		return (path);
	end_slash = get_end_slashes(cons_slash);
	newpath = try_strjoin_free(
			try_substr(path, 0, cons_slash - path), end_slash);
	free(path);
	return (cd_replace_non_leading_consecutive_slashes(newpath));
}
