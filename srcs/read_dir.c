/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:24 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/07 02:17:58 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			dircheck(char *dir)
{
	DIR		*dirp;

	if ((dirp = opendir(dir)))
	{
		closedir(dirp);
		return (1);
	}
	return (0);
}

int			diropen(char *opt, char **lstdir, char **buff)
{
	size_t			i;

	sort_dir(opt, lstdir, NULL);
	i = 0;
	while (lstdir[i])
	{
		if (i)
			fill_nchar(buff, '\n', 1);
		dirlst(opt, lstdir[i++], buff);
	}
	return (0);
}

size_t		nbrcontdir(char *dir)
{
	DIR		*dirp;
	size_t	i;

	dirp = opendir(dir);
	i = 0;
	while (readdir(dirp))
		i++;
	closedir(dirp);
	return (i);
}

static void	searchdir(char *opt, char *dir, char **lstcont, char **buff)
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
		if (dircheck(tmp2) && ft_strcmp(lstcont[i], "..") != 0 &&
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

int			dirlst(char *opt, char *dir, char **buff)
{
	struct dirent	*dirc;
	DIR				*dirp;
	char			**lstcont;
	size_t			i;

	lstcont = (char **)ft_memalloc(sizeof(char *) * (nbrcontdir(dir) + 1));
	dirp = opendir(dir);
	i = 0;
	while ((dirc = readdir(dirp)))
		lstcont[i++] = ft_strdup(dirc->d_name);
	sort_dir(opt, lstcont, dir);
	if (ft_strchr(opt, 'l'))
		buff_idir(opt, dir, lstcont, buff);
	else
		buff_dir(opt, dir, lstcont, buff);
	closedir(dirp);
	fill_nchar(buff, '\n', 1);
	if (ft_strchr(opt, 'R'))
		searchdir(opt, dir, lstcont, buff);
	i = 0;
	while (lstcont[i])
		free(lstcont[i++]);
	free(lstcont);
	return (0);
}
