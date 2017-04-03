/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:14:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 11:13:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			dircheck(char *dir, char **buff)
{
	DIR			*dirp;
	struct stat	atr;

	lstat(dir, &atr);
	errno = 0;
	if (!(dirp = opendir(dir)))
	{
		if (errno != ENOTDIR)
			print_err_perm(buff, dir);
		return (0);
	}
	else if (file_type(atr.st_mode) == 'd')
	{
		closedir(dirp);
		return (1);
	}
	closedir(dirp);
	return (0);
}

void		tmp_free(char ***tmp)
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

int			buff_one(char *opt, char **lstcont, char **buff)
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

void		printfile_err(char **err, char **opt)
{
	int	i;

	i = 0;
	while (err[i])
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(err[i]);
		opt[0][ft_strlen(*opt)] = '9';
		i++;
		free(err[i]);
	}
	free(err);
}

int			print_err_perm(char **buff, char *dir)
{
	print_buff(buff);
	perror(dir);
	return (1);
}
