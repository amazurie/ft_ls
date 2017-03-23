/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:24 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 17:55:38 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	diropen3(char *opt, char **lstdir, char **buff, size_t **i)
{
	size_t		*len;
	struct stat	atr;

	len_ls(lstdir, &atr, &len);
	while (lstdir[(*i)[0]])
	{
		lstat(lstdir[(*i)[0]++], &atr);
		if (file_type(atr.st_mode) != 'd')
		{
			(*i)[2] = 1;
			if (ft_strchr(opt, 'l'))
			{
				buff_cont2(lstdir[(*i)[0] - 1], atr, len, buff);
				buffncat(buff, " ", (*i)[1]);
				buffcat(buff, lstdir[(*i)[0] - 1]);
				buff_link(atr, buff, lstdir[(*i)[0] - 1]);
				fill_nchar(buff, '\n', 1);
			}
			else if (!ft_strchr(opt, 'l'))
				buffncat(buff, " ", (*i)[1]);
		}
	}
	free(len);
}

static int	diropen2(char *opt, char **lstdir, char **buff)
{
	size_t		*i;

	i = (size_t *)ft_memalloc(sizeof(size_t) * 4);
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (lstdir[i[0]])
		if (i[1] < ft_strlen(lstdir[i[0]++]))
			i[1] = ft_strlen(lstdir[i[0] - 1]);
	sort_dir(opt, lstdir, NULL);
	i[0] = 0;
	diropen3(opt, lstdir, buff, &i);
	buff[0][ft_strlen((*buff)) - 1] = 0;
	free(i);
	return (i[2]);
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

	if (!(dirp = opendir(dir)))
		return (print_err_perm(buff, dir));
	lstcont = (char **)ft_memalloc(sizeof(char *) * (nbrcontdir(dir) + 1));
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
