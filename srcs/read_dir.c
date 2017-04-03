/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:24 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 11:14:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	diropen3(char *opt, char **lstdir, char **buff, size_t **i)
{
	size_t		*len;
	struct stat	*atr;

	atr = (struct stat *)ft_memalloc(sizeof(struct stat) * ((*i)[0] + 1));
	(*i)[0] = -1;
	while (lstdir[++(*i)[0]])
		lstat(lstdir[(*i)[0]], &atr[(*i)[0]]);
	len_ls(lstdir, atr, &len);
	(*i)[0] = 0;
	while (lstdir[(*i)[0]])
	{
		if (file_type(atr[(*i)[0]].st_mode) != 'd')
		{
			(*i)[2] = 1;
			if (ft_strchr(opt, 'l'))
				buff_cont2(lstdir[(*i)[0]], atr[(*i)[0]], len, buff);
			if (ft_strchr(opt, 'l'))
				diropenl(lstdir, buff, i, atr);
			else
				diropenc(opt, lstdir, buff, i);
		}
		(*i)[0]++;
	}
	free(len);
	free(atr);
}

static int	diropen2(char *opt, char **lstdir, char **buff)
{
	size_t	*i;
	int		j;

	i = (size_t *)ft_memalloc(sizeof(size_t) * 4);
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (lstdir[i[0]])
		if (i[1] < ft_strlen(lstdir[i[0]++]))
			i[1] = ft_strlen(lstdir[i[0] - 1]);
	sort_dir(opt, lstdir, NULL);
	diropen3(opt, lstdir, buff, &i);
	buff[0][ft_strlen((*buff)) - 1] = 0;
	j = i[2];
	free(i);
	return (j);
}

int			diropen(char *opt, char **lstdir, char **buff)
{
	size_t		i;
	int			k;
	int			j;
	struct stat	atr;

	k = 0;
	k = diropen2(opt, lstdir, buff);
	if (k)
		fill_nchar(buff, '\n', 1);
	i = 0;
	j = 0;
	while (lstdir[i])
	{
		lstat(lstdir[i++], &atr);
		if (file_type(atr.st_mode) == 'd')
		{
			if (j || (k && ft_strchr(opt, '9')))
				fill_nchar(buff, '\n', 1);
			dirlst(opt, lstdir[i - 1], buff);
			j = 1;
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
