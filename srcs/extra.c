/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:34:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 17:50:54 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		file_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	return ('?');
}

void	searchdir(char *opt, char *dir, char **lstcont, char **buff)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = 0;
	while (lstcont[i])
	{
		tmp = ft_strjoin(dir, "/");
		tmp2 = ft_strjoin(tmp, lstcont[i]);
		free(tmp);
		if (dircheck(tmp2, buff) && ft_strcmp(lstcont[i], "..") != 0 &&
				ft_strcmp(lstcont[i], ".") != 0 &&
				(lstcont[i][0] != '.' || ft_strchr(opt, 'a')))
		{
			fill_nchar(buff, '\n', 1);
			dirlst(opt, tmp2, buff);
		}
		free(tmp2);
		i++;
	}
}

void		set_pathdir(char *opt, char *dir, char **lstcont, struct stat *atr)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = 0;
	while (lstcont[i])
	{
		if (lstcont[i][0] != '.' || ft_strchr(opt, 'a'))
		{
			tmp = ft_strjoin(dir, "/");
			tmp2 = ft_strjoin(tmp, lstcont[i]);
			lstat(tmp2, &atr[i]);
			free(tmp);
			free(tmp2);
		}
		else
			ft_bzero(lstcont[i], ft_strlen(lstcont[i]));
		i++;
	}
}

void		buff_dir_name(char *opt, char *dir, char **buff)
{
	if (ft_strchr(opt, '9') && ft_strcmp(dir, ".") != 0)
		buffcat(buff, dir);
	if (ft_strchr(opt, '9') && ft_strcmp(dir, ".") != 0)
		buffcat(buff, ":\n");
}

void		free_lst(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}
