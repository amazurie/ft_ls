/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:14:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/07 02:07:13 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	mj(struct stat atr, char **buff, size_t *len)
{
	char	*tmp;
	char	tmp2;

	tmp2 = file_type(atr.st_mode);
	if (tmp2 == 'c' || tmp2 == 'b')
	{
		buff_num(buff, major(atr.st_rdev));
		buffcat(buff, " ");
		buff_num(buff, minor(atr.st_rdev));
		buffcat(buff, " ");
	}
	else
	{
		tmp = ft_itoa(atr.st_size);
		fill_nchar(buff, ' ', len[1] - ft_strlen(tmp));
		buffcat(buff, tmp);
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

void		buff_link(struct stat atr, char **buff, char *cont, char *tmp)
{
	char	*tmp2;

	tmp2 = (char *)ft_memalloc(500);
	if (file_type(atr.st_mode) == 'l')
	{
		buffcat(buff, cont);
		buffcat(buff, " -> ");
		readlink(tmp, tmp2, 499);
		buffcat(buff, tmp2);
	}
	free(tmp2);
}

void	tmp_free(char ***tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
			free(tmp[i][j++]);
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

int		buff_one(char *opt, char **lstcont, char **buff)
{
	size_t i;

	if (ft_strchr(opt, '1'))
	{
		i = 0;
		while (lstcont[i])
		{
			buffcat(buff, lstcont[i]);
			if (lstcont[++i])
				buffcat(buff, "\n");
		}
		return (1);
	}
	return (0);
}
