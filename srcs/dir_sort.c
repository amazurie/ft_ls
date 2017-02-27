/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/07 05:08:47 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		sort_alpha(char *opt, char **lstdir)
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

static size_t	sort_sec(char **lstdir, char *path, struct stat atr, size_t i)
{
	struct stat	atr2;
	char		*tmp;
	char		*tmp2;
	time_t		jktm[3];

	jktm[1] = 0;
	jktm[0] = i;
	jktm[2] = atr.st_mtime;
	while (++jktm[0] && lstdir[jktm[0]])
	{
		tmp = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp, lstdir[jktm[0]]);
		if (lstat(tmp2, &atr2) == 0 || stat(tmp2, &atr2) == 0)
		{
			if (jktm[2] < atr2.st_mtime)
				jktm[1] = jktm[0];
			if (jktm[2] < atr2.st_mtime)
				jktm[2] = atr2.st_mtime;
		}
		free(tmp);
		free(tmp2);
	}
	if (jktm[1] > 0)
		ft_strswap(&lstdir[i], &lstdir[jktm[1]]);
	return (i);
}

static size_t	sort_rsec(char **lstdir, char *path, struct stat atr, size_t i)
{
	struct stat	atr2;
	char		*tmp;
	char		*tmp2;
	time_t		jktm[3];

	jktm[1] = 0;
	jktm[0] = i;
	jktm[2] = atr.st_mtime;
	while (++jktm[0] && lstdir[jktm[0]])
	{
		tmp = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp, lstdir[jktm[0]]);
		if (lstat(tmp2, &atr2) == 0 || stat(tmp2, &atr2) == 0)
		{
			if (jktm[2] > atr2.st_mtime)
				jktm[1] = jktm[0];
			if (jktm[2] > atr2.st_mtime)
				jktm[2] = atr2.st_mtime;
		}
		free(tmp);
		free(tmp2);
	}
	if (jktm[1] > 0)
		ft_strswap(&lstdir[i], &lstdir[jktm[1]]);
	return (i);
}

static void		sort_time(char *opt, char **lstdir, char *path)
{
	struct stat	atr;
	char		*tmp;
	char		*tmp2;
	size_t		i;

	i = 0;
	while (lstdir[i])
	{
		tmp = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp, lstdir[i]);
		if (lstat(tmp2, &atr) == 0 || stat(tmp2, &atr) == 0)
		{
			if (ft_strchr(opt, 'r'))
				i = sort_rsec(lstdir, path, atr, i);
			else
				i = sort_sec(lstdir, path, atr, i);
		}
		i++;
		free(tmp);
		free(tmp2);
	}
	sort_alphat(opt, lstdir, path);
}

int				sort_dir(char *opt, char **lstdir, char *path)
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
