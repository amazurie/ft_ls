/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:36:54 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/27 13:18:17 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t			sort_alphat2(char *opt, char **lstdir, size_t i)
{
	if (ft_strcmp(lstdir[i], lstdir[i + 1]) > 0
			&& !ft_strchr(opt, 'r'))
	{
		ft_strswap(&lstdir[i], &lstdir[i + 1]);
		(i > 0) ? i-- : 0;
	}
	else if ((ft_strcmp(lstdir[i], lstdir[i + 1]) < 0)
			&& ft_strchr(opt, 'r'))
	{
		ft_strswap(&lstdir[i], &lstdir[i + 1]);
		(i > 0) ? i-- : 0;
	}
	else
		i++;
	return (i);
}

void			sort_alphat(char *opt, char **lstdir, char *path)
{
	struct stat	atr;
	struct stat	atr2;
	char		**tmp;
	size_t		i;
	size_t		j;

	tmp = (char **)ft_memalloc(sizeof(char *) * 5);
	i = 0;
	while (lstdir[i] && lstdir[i + 1])
	{
		tmp[1] = ft_strjoin(path, "/");
		tmp[2] = ft_strjoin(tmp[1], lstdir[i]);
		tmp[3] = ft_strjoin(path, "/");
		tmp[4] = ft_strjoin(tmp[4], lstdir[i + 1]);
		stat(tmp[2], &atr);
		stat(tmp[4], &atr2);
		if (atr.st_mtime == atr2.st_mtime)
			i = sort_alphat2(opt, lstdir, i);
		else
			i++;
		j = 0;
		while (j < 4)
			free(tmp[j++]);
	}
	free(tmp);
}

static size_t	sort_sec(char **lstdir, char *path, struct stat atr, size_t i)
{
	struct stat	atr2;
	char		*tmp2;
	size_t		j;
	size_t		k;
	long long	tm;

	k = 0;
	j = i;
	tm = atr.st_size;
	while (++j && lstdir[j])
	{
		tmp2 = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp2, lstdir[j]);
		if (lstat(tmp2, &atr2) == 0 || stat(tmp2, &atr2) == 0)
		{
			if (tm < atr2.st_size)
				k = j;
			if (tm < atr2.st_size)
				tm = atr2.st_size;
		}
		free(tmp2);
	}
	if (k > 0)
		ft_strswap(&lstdir[i], &lstdir[k]);
	return (i);
}

static size_t	sort_rsec(char **lstdir, char *path, struct stat atr, size_t i)
{
	struct stat	atr2;
	char		*tmp2;
	size_t		j;
	size_t		k;
	long long	tm;

	k = 0;
	j = i;
	tm = atr.st_size;
	while (++j && lstdir[j])
	{
		tmp2 = ft_strjoin(path, "/");
		tmp2 = ft_strjoin(tmp2, lstdir[j]);
		if (lstat(tmp2, &atr2) == 0 || stat(tmp2, &atr2) == 0)
		{
			if (tm > atr2.st_size)
				k = j;
			if (tm > atr2.st_size)
				tm = atr2.st_size;
		}
		free(tmp2);
	}
	if (k > 0)
		ft_strswap(&lstdir[i], &lstdir[k]);
	return (i);
}

void			sort_size(char *opt, char **lstdir, char *path)
{
	struct stat	atr;
	char		*tmp;
	size_t		i;

	i = 0;
	while (lstdir[i])
	{
		tmp = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp, lstdir[i]);
		if (lstat(tmp, &atr) == 0 || stat(tmp, &atr) == 0)
		{
			if (ft_strchr(opt, 'r'))
				i = sort_rsec(lstdir, path, atr, i);
			else
				i = sort_sec(lstdir, path, atr, i);
		}
		i++;
		free(tmp);
	}
	sort_alphat(opt, lstdir, path);
}
