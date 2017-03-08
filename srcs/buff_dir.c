/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:24:31 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/08 11:31:38 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	nbr_hidden(char *opt, char **lstcont)
{
	size_t	i;
	size_t	j;

	if (ft_strchr(opt, 'a'))
		return (0);
	i = 0;
	j = 0;
	while (lstcont[i])
		if (lstcont[i++][0] == '.')
			j++;
	return (j);
}

static size_t	nname(char *opt, char **lstcont, struct winsize w, size_t *len)
{
	size_t			nbr;
	size_t			i;

	i = 0;
	*len = 0;
	while (lstcont[i])
	{
		if (ft_strlen(lstcont[i]) >= *len)
			*len = ft_strlen(lstcont[i]) + 1;
		i++;
	}
	if (w.ws_col && (i - nbr_hidden(opt, lstcont)) * *len > w.ws_col)
	{
		nbr = w.ws_col / *len;
		if (nbr * 2 > i)
			nbr = ((i + (i % 2 != 0)) - nbr_hidden(opt, lstcont)) / 2;
	}
	else if (!w.ws_col)
	{
		*len = 0;
		nbr = 1;
	}
	else
		nbr = i - nbr_hidden(opt, lstcont);
	return (nbr);
}

void			set_nbr(char *opt, char **lstcont, size_t **nbr)
{
	struct winsize	w;

	*nbr = (size_t *)ft_memalloc(sizeof(size_t) * 6);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	nbr[0][4] = 0;
	nbr[0][1] = 0;
	nbr[0][3] = 0;
	while (lstcont[nbr[0][1]])
		if (lstcont[nbr[0][1]++][0] != '.' || ft_strchr(opt, 'a'))
			nbr[0][3]++;
	if (!(nbr[0][0] = nname(opt, lstcont, w, &nbr[0][2])))
		nbr[0][0] = 1;
	nbr[0][1] = 0;
	while (nbr[0][1] * nbr[0][0] < nbr[0][3])
		nbr[0][1]++;
	if (nbr[0][0] * nbr[0][1] - (nbr[0][3] -
				nbr_hidden(opt, lstcont)) >= nbr[0][0])
		nbr[0][1]--;
	if (w.ws_col > nbr[0][2] * nbr[0][3])
		nbr[0][1] = 1;
}

static char		**set_dir(char *opt, char **lstcont)
{
	char	**lst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (lstcont[i])
		if (lstcont[i++][0] != '.' || ft_strchr(opt, 'a'))
			j++;
	lst = (char **)ft_memalloc(sizeof(char *) * (j + 1));
	i = 0;
	j = 0;
	while (lstcont[i])
	{
		if (lstcont[i][0] != '.' || ft_strchr(opt, 'a'))
		{
			lst[j] = ft_strdup(lstcont[i]);
			j++;
		}
		i++;
	}
	return (lst);
}

void			buff_dir(char *opt, char *dir, char **lstcont, char **buff)
{
	char		**tmp;
	size_t		*nbr;

	tmp = set_dir(opt, lstcont);
	set_nbr(opt, tmp, &nbr);
	buff_dir_name(opt, dir, buff);
	while (nbr[4] < nbr[1] && !buff_one(opt, tmp, buff))
	{
		nbr[5] = 0;
		while (nbr[5] < nbr[0])
		{
			if (nbr[4] + nbr[5]++ * nbr[1] < nbr[3])
			{
				buffcat(buff, tmp[nbr[4] + (nbr[5] - 1) * nbr[1]]);
				fill_nchar(buff, ' ', nbr[2] -
						ft_strlen(tmp[nbr[4] + (nbr[5] - 1) * nbr[1]]));
				if (ft_strchr(opt, '1'))
					buffcat(buff, "\n");
			}
		}
		if (nbr[4]++ + 1 < nbr[1] && (nbr[5] > 1 || nbr[0] == 1))
			buffcat(buff, "\n");
	}
	free_lst(tmp);
	free(nbr);
}
