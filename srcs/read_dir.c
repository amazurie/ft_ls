/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:24 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/01 12:18:17 by amazurie         ###   ########.fr       */
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

static int	diropen2(char *opt, char **lstdir, char **buff)
{
	size_t		i;
	size_t		j;
	size_t		k;
	struct stat	atr;

	i = 0;
	j = 0;
	k = 0;
	while (lstdir[i])
		if (j < ft_strlen(lstdir[i++]))
			j = ft_strlen(lstdir[i - 1]);
	sort_dir(opt, lstdir, NULL);
	i = 0;
	while (lstdir[i])
	{
		stat(lstdir[i++], &atr);
		if (file_type(atr.st_mode) != 'd')
		{
			k = 1;
			buffcat(buff, lstdir[i - 1]);
			buffncat(buff, " ", j);
		}
	}
	return (k);
}

int			diropen(char *opt, char **lstdir, char **buff)
{
	size_t		i;
	size_t		k;
	struct stat	atr;

	k = 0;
	k = diropen2(opt, lstdir, buff);
	if (k)
		fill_nchar(buff, '\n', 1);
	i = 0;
	while (lstdir[i])
	{
		stat(lstdir[i++], &atr);
		if (file_type(atr.st_mode) == 'd')
		{
			if (i - 1)
				fill_nchar(buff, '\n', 1);
			dirlst(opt, lstdir[i - 1], buff);
		}
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
