/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:10:18 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 15:33:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	searchdir(char *opt, char *dir, char **lstcont, char **buff)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = 0;
	while (lstcont[i])
	{
		tmp = ft_strjoin(dir, "/");
		tmp2 = ft_strjoin(tmp, lstcont[i]);
		free(tmp);
		if (dircheck(tmp2) && ft_strcmp(lstcont[i], "..") != 0 &&
				ft_strcmp(lstcont[i], ".") != 0 &&
				(lstcont[i][0] != '.' || ft_strchr(opt, 'a')))
		{
			fill_nchar(buff, '\n', 1);
			dirlst(opt, tmp2, buff);
		}
		free(tmp2);
		i++;
	}
}

int		dircheck(char *dir)
{
	DIR			*dirp;
	struct stat	atr;

	lstat(dir, &atr);
	if ((dirp = opendir(dir)) && file_type(atr.st_mode) == 'd')
	{
		closedir(dirp);
		return (1);
	}
	return (0);
}

void	printfile_err(char **err, char **opt)
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

int		print_err_perm(char **buff)
{
	print_buff(buff);
	ft_putstr_fd("ft_ls: a: Permission denied\n", 2);
	return (1);
}
