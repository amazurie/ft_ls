/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 17:59:07 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sort_alpha(char *opt, char **lstdir)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (lstdir[i])
	{
		j = i + 1;
		while (lstdir[j])
		{
			if (ft_strcmp(lstdir[i], lstdir[j]) >= 0 &&
					!ft_strchr(opt, 'r'))
				ft_strswap(&lstdir[i], &lstdir[j]);
			if (ft_strcmp(lstdir[i], lstdir[j]) < 0 &&
					ft_strchr(opt, 'r'))
				ft_strswap(&lstdir[i], &lstdir[j]);
			j++;
		}
		i++;
	}
}

static void	sort_rsec(char **lstdir, char **tmp, struct stat **atr, size_t i)
{
	int		j;

	j = i;
	while (lstdir[j])
	{
		tmp[2] = ft_strjoin(tmp[0], lstdir[j]);
		lstat(tmp[2], atr[1]);
		if (atr[0]->st_mtime > atr[1]->st_mtime)
			ft_strswap(&lstdir[i], &lstdir[j]);
		if (atr[0]->st_mtime > atr[1]->st_mtime)
			lstat(tmp[2], atr[0]);
		else if (atr[0]->st_mtime == atr[1]->st_mtime)
		{
			if ((atr[0]->st_mtimespec.tv_nsec > atr[1]->st_mtimespec.tv_nsec)
				|| (atr[0]->st_mtimespec.tv_nsec == atr[1]->st_mtimespec.tv_nsec
				&& ft_strcmp(lstdir[i], lstdir[j]) <= 0))
			{
				ft_strswap(&lstdir[i], &lstdir[j]);
				lstat(tmp[2], atr[0]);
			}
		}
		j++;
	}
}

static void	sort_sec(char **lstdir, char **tmp, struct stat **atr, size_t i)
{
	int		j;

	j = i;
	while (lstdir[j])
	{
		tmp[2] = ft_strjoin(tmp[0], lstdir[j]);
		lstat(tmp[2], atr[1]);
		if (atr[0]->st_mtime < atr[1]->st_mtime)
			ft_strswap(&lstdir[i], &lstdir[j]);
		if (atr[0]->st_mtime < atr[1]->st_mtime)
			lstat(tmp[2], atr[0]);
		else if (atr[0]->st_mtime == atr[1]->st_mtime)
		{
			if ((atr[0]->st_mtimespec.tv_nsec < atr[1]->st_mtimespec.tv_nsec)
				|| (atr[0]->st_mtimespec.tv_nsec == atr[1]->st_mtimespec.tv_nsec
				&& ft_strcmp(lstdir[i], lstdir[j]) >= 0))
			{
				ft_strswap(&lstdir[i], &lstdir[j]);
				lstat(tmp[2], atr[0]);
			}
		}
		free(tmp[2]);
		j++;
	}
}

static void	sort_time(char *opt, char **lstdir, char *path)
{
	struct stat	**atr;
	char		**tmp;
	int			i;

	atr = (struct stat **)ft_memalloc(sizeof(struct stat *) * 3);
	atr[0] = (struct stat *)ft_memalloc(sizeof(struct stat));
	atr[1] = (struct stat *)ft_memalloc(sizeof(struct stat));
	tmp = (char **)ft_memalloc(sizeof(char *) * 4);
	i = -1;
	while (lstdir[++i])
	{
		tmp[0] = ft_strjoin(path, "/");
		tmp[1] = ft_strjoin(tmp[0], lstdir[i]);
		lstat(tmp[1], atr[0]);
		if (ft_strchr(opt, 'r'))
			sort_rsec(lstdir, tmp, atr, i);
		else
			sort_sec(lstdir, tmp, atr, i);
		free(tmp[0]);
		free(tmp[1]);
	}
	free(atr[0]);
	free(atr[1]);
	free(atr);
	free(tmp);
}

int			sort_dir(char *opt, char **lstdir, char *path)
{
	if (ft_strchr(opt, 'f'))
		return (0);
	if (ft_strchr(opt, 't'))
		sort_time(opt, lstdir, path);
	else if (ft_strchr(opt, 'S'))
		sort_size(opt, lstdir, path);
	else
		sort_alpha(opt, lstdir);
	return (0);
}
