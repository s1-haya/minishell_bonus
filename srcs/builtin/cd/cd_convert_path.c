/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_convert_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:29:32 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/30 13:48:19 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	cd_put_error_no_pwd(char *path, t_data *d);
char	*cd_delete_dot_slash(char *path, char *last_ds);
char	*cd_delete_dotdot(char *path, char *last_ddc, bool *nonexistant_path);
void	cd_put_error_file(const char *og_path, t_data *d);
void	cd_put_error_file_dir(const char *og_path, t_data *d);
char	*cd_delete_dotdot_if_needed(char *path, char *last_ddc);
char	*cd_delete_slash(char *path);
void	cd_exec(const char *og_path, char *path, bool is_cdpath, t_data *d);

static char	*cd_join_pwd(char *path, t_data *d)
{
	char	*newpath;

	if (d->pwd == NULL)
	{
		cd_put_error_no_pwd(path, d);
		return (NULL);
	}
	if (d->pwd[ft_strlen(d->pwd) - 1] == '/')
		newpath = try_strdup(d->pwd);
	else
		newpath = try_strjoin(d->pwd, "/");
	newpath = try_strjoin_free(newpath, path);
	free(path);
	return (newpath);
}

void	cd_convert_path_and_exec(const char *og_path, char *path,
									t_data *d, bool is_cdpath)
{
	bool	nonexistant_path;

	nonexistant_path = false;
	if (path == NULL)
		return ;
	if (*path != '/')
		path = cd_join_pwd(path, d);
	if (path == NULL)
		return ;
	path = cd_delete_dot_slash(path, path);
	path = cd_delete_dotdot(path, path, &nonexistant_path);
	if (path == NULL && !nonexistant_path)
		return (cd_put_error_file(og_path, d));
	else if (path == NULL && nonexistant_path)
		return (cd_put_error_file_dir(og_path, d));
	path = cd_delete_dotdot_if_needed(path, path);
	path = cd_delete_slash(path);
	cd_exec(og_path, path, is_cdpath, d);
}
