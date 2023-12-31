/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:17 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 20:07:34 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."
#define DDCS "/../"

char	*cd_get_pre_comp(char *path, char *ddc);
bool	cd_is_slash_comp(char *pre_comp, char *ddc);
char	*cd_delete_dotdot(char *path, char *last_ddc, bool *nonexistant_path);

bool	is_dotdotcomp(char *path)
{
	const char	*dddc = "//..";
	const char	*dddcs = "//../";

	return (
		(ft_strncmp(path, DDC, ft_strlen(DDC)) == 0
			&& *(path + ft_strlen(DDC)) == '\0')
		|| ft_strncmp(path, DDCS, ft_strlen(DDCS)) == 0
		|| (ft_strncmp(path, dddc, ft_strlen(dddc)) == 0
			&& *(path + ft_strlen(dddc)) == '\0')
		|| ft_strncmp(path, dddcs, ft_strlen(dddcs)) == 0
	);
}

static bool	cd_is_dir(char *path, char *dirpath, bool *nonexistant_path)
{
	struct stat	sb;
	bool		is_dir;

	if (stat(dirpath, &sb) == -1)
	{
		free(dirpath);
		free(path);
		*nonexistant_path = true;
		return (false);
	}
	if (S_ISDIR(sb.st_mode))
		is_dir = true;
	else
	{
		is_dir = false;
		free(path);
	}
	free(dirpath);
	return (is_dir);
}

char	*skip_consecutive_slashes(char *path)
{
	while (*path != '\0')
	{
		if (*path != '/')
			break ;
		path++;
	}
	return (path);
}

static char	*cd_make_newpath(char *path, char *pre_comp, char *ddc,
							bool *nonexistant_path)
{
	char		*newpath;

	if (cd_is_slash_comp(pre_comp, ddc))
		return (
			cd_delete_dotdot(path, (ddc + ft_strlen(ddc)), nonexistant_path));
	if (!cd_is_dir(path, try_substr(path, 0, ddc - path), nonexistant_path))
		return (NULL);
	if (pre_comp != path)
	{
		newpath = try_substr(path, 0, pre_comp - path);
		newpath = try_strjoin_free(newpath, (ddc + ft_strlen(DDC)));
	}
	else
	{
		newpath = try_substr(path, 0, skip_consecutive_slashes(path) - path);
		newpath = try_strjoin_free(newpath, (ddc + ft_strlen(DDC) + 1));
	}
	free(path);
	return (cd_delete_dotdot(newpath, newpath, nonexistant_path));
}

char	*cd_delete_dotdot(char *path, char *last_ddc, bool *nonexistant_path)
{
	char			*ddc;
	char			*pre_comp;
	const size_t	ddc_len = ft_strlen(DDC);

	ddc = ft_strstr(last_ddc, DDC);
	if (ddc == NULL)
		return (path);
	if (!is_dotdotcomp(ddc) || ddc == path)
		return (cd_delete_dotdot(path, ddc + ddc_len, nonexistant_path));
	if (!cd_is_dir(path, try_substr(path, 0, ddc - path), nonexistant_path))
		return (NULL);
	pre_comp = cd_get_pre_comp(path, ddc);
	if (is_dotdotcomp(pre_comp))
		return (cd_delete_dotdot(path, (ddc + ddc_len), nonexistant_path));
	return (cd_make_newpath(path, pre_comp, ddc, nonexistant_path));
}
