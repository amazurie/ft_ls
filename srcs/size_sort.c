/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:36:54 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 18:02:28 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		if (lstat(tmp2, &atr2) == 0)
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
		if (lstat(tmp2, &atr2) == 0)
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
		if (lstat(tmp, &atr) == 0)
		{
			if (ft_strchr(opt, 'r'))
				i = sort_rsec(lstdir, path, atr, i);
			else
				i = sort_sec(lstdir, path, atr, i);
		}
		i++;
		free(tmp);
	}
}
