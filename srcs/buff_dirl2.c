/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_dirl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:37:54 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 17:07:10 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		block_size(char *opt, char *dir, char **lstcont)
{
	struct stat	atr;
	size_t		size;
	size_t		i;
	char		*tmp;
	char		*tmp2;

	i = 0;
	size = 0;
	while (lstcont[i])
	{
		if (lstcont[i++][0] != '.' || ft_strchr(opt, 'a'))
		{
			tmp = ft_strjoin(dir, "/");
			tmp2 = ft_strjoin(tmp, lstcont[i - 1]);
			if (lstat(tmp2, &atr) == 0)
				size += atr.st_blocks;
			free(tmp);
			free(tmp2);
		}
	}
	return (size);
}

static void	len_ls2(struct stat atr, size_t **len)
{
	char	*tmp;
	size_t	j;

	j = ft_strlen(getgrgid(atr.st_gid)->gr_name) + 1;
	if (len[0][3] <= j)
		len[0][3] = j;
	if (file_type(atr.st_mode) != 'c'
			&& file_type(atr.st_mode) != 'b')
		return ;
	tmp = ft_itoa(major(atr.st_rdev));
	j = ft_strlen(tmp) + 1;
	if (len[0][4] <= j)
		len[0][4] = j;
	free(tmp);
	tmp = ft_itoa(minor(atr.st_rdev));
	j = ft_strlen(tmp) + 1;
	if (len[0][5] <= j)
		len[0][5] = j;
	free(tmp);
}

void		len_ls(char **lstcont, struct stat *atr, size_t **len)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	*len = (size_t *)ft_memalloc(sizeof(size_t) * 6);
	i = 0;
	len[0][4] = 0;
	len[0][5] = 0;
	while (lstcont[i])
	{
		tmp = ft_itoa(atr[i].st_nlink);
		if (len[0][0] <= ft_strlen(tmp))
			len[0][0] = ft_strlen(tmp) + 1;
		free(tmp);
		tmp = ft_itoa(atr[i].st_size);
		if (len[0][1] <= ft_strlen(tmp))
			len[0][1] = ft_strlen(tmp) + 1;
		free(tmp);
		j = ft_strlen(getpwuid(atr[i].st_uid)->pw_name) + 1;
		if (len[0][2] <= j)
			len[0][2] = j;
		len_ls2(atr[i], len);
		i++;
	}
}

static void	mj(struct stat atr, char **buff, size_t *len)
{
	char	*tmp;
	char	tmp2;

	tmp2 = file_type(atr.st_mode);
	if (tmp2 == 'c' || tmp2 == 'b')
	{
		tmp = ft_itoa(major(atr.st_rdev));
		fill_nchar(buff, ' ', len[4] - ft_strlen(tmp));
		buffcat(buff, tmp);
		buffcat(buff, ",");
		tmp = ft_itoa(minor(atr.st_rdev));
		fill_nchar(buff, ' ', len[5] - ft_strlen(tmp));
		buffcat(buff, tmp);
	}
	else
	{
		fill_nchar(buff, ' ', len[4] + len[5] - 1);
		tmp = ft_itoa(atr.st_size);
		fill_nchar(buff, ' ', len[1] - ft_strlen(tmp));
		buffcat(buff, tmp);
		buffcat(buff, " ");
		free(tmp);
	}
}

void		time_cont(struct stat atr, char **buff, size_t *len)
{
	time_t	tm;

	mj(atr, buff, len);
	tm = atr.st_mtime;
	if (time(NULL) - tm > 15724800 || time(NULL) - tm < 0)
	{
		ctime(&tm);
		buffncat(buff, (ctime(&tm) + 3), 8);
		buffncat(buff, (ctime(&tm) + 19), 5);
	}
	else
	{
		ctime(&tm);
		buffncat(buff, (ctime(&tm) + 3), 13);
	}
}
