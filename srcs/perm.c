/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:00:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 17:02:10 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*perm(int i)
{
	if (i == 7)
		return ("rwx");
	if (i == 6)
		return ("rw-");
	if (i == 5)
		return ("r-x");
	if (i == 4)
		return ("r--");
	if (i == 3)
		return ("-wx");
	if (i == 2)
		return ("-w-");
	if (i == 1)
		return ("--x");
	return ("---");
}

static void	buff_permi2(struct stat atr, char **buff, char **tmp)
{
	*tmp = ft_strdup(perm((S_IRWXG & atr.st_mode) / 8));
	if ((S_ISGID & atr.st_mode))
	{
		if ((*tmp)[2] == '-')
			(*tmp)[2] = 'S';
		else
			(*tmp)[2] = 's';
	}
	buffcat(buff, *tmp);
	free(*tmp);
	*tmp = ft_strdup(perm(S_IRWXO & atr.st_mode));
	if ((S_ISVTX & atr.st_mode))
	{
		if ((*tmp)[2] == '-')
			(*tmp)[2] = 'T';
		else
			(*tmp)[2] = 't';
	}
	buffcat(buff, *tmp);
}

void		buff_permi(struct stat atr, char **buff)
{
	char *tmp;

	tmp = ft_strdup(perm((S_IRWXU & atr.st_mode) / 64));
	if ((S_ISUID & atr.st_mode))
	{
		if (tmp[2] == '-')
			tmp[2] = 'S';
		else
			tmp[2] = 's';
	}
	buffcat(buff, tmp);
	free(tmp);
	buff_permi2(atr, buff, &tmp);
	free(tmp);
}
