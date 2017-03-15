/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:10:18 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/15 12:31:25 by amazurie         ###   ########.fr       */
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

void	printfile_err(char **err, char **opt)
{
	int	i;

	i = 0;
	while (err[i])
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(err[i]);
		opt[0][ft_strlen(*opt)] = '9';
		if (ft_strlen_chr(*opt, 'r') < ft_strlen(*opt))
			opt[0][ft_strlen_chr(*opt, 'r')] = ' ';
		i++;
		free(err[i]);
	}
	free(err);
}
