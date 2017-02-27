/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_dirl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:37:54 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/07 02:28:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	len_ls(char **lstcont, struct stat *atr, size_t **len)
{
	char	*tmp;
	size_t	i;

	*len = (size_t *)ft_memalloc(sizeof(size_t) * 3);
	i = 0;
	while (lstcont[i])
	{
		if (lstcont[i][0] != 0)
		{
			tmp = ft_itoa(atr[i].st_nlink);
			if (len[0][0] <= ft_strlen(tmp))
				len[0][0] = ft_strlen(tmp) + 1;
			free(tmp);
			tmp = ft_itoa(atr[i].st_size);
			if (len[0][1] <= ft_strlen(tmp))
				len[0][1] = ft_strlen(tmp) + 1;
			free(tmp);
		}
		i++;
	}
}

char		get_atr(char *path)
{
	int		attr;
	acl_t	acl;

	attr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (attr > 0)
	{
		acl_free((void*)acl);
		return ('@');
	}
	else if (acl)
	{
		acl_free((void*)acl);
		return ('+');
	}
	acl_free((void*)acl);
	return (' ');
}

static void	buff_cont2(char *dir, struct stat atr, size_t *len, char **buff)
{
	char	*tmp;
	char	tmp2;

	tmp2 = file_type(atr.st_mode);
	fill_nchar(buff, tmp2, 1);
	buffcat(buff, perm((S_IRWXU & atr.st_mode) / 64));
	buffcat(buff, perm((S_IRWXG & atr.st_mode) / 8));
	buffcat(buff, perm(S_IRWXO & atr.st_mode));
	fill_nchar(buff, get_atr(dir), 1);
	tmp = ft_itoa(atr.st_nlink);
	fill_nchar(buff, ' ', len[0] - ft_strlen(tmp));
	buffcat(buff, tmp);
	buffcat(buff, " ");
	buffcat(buff, getpwuid(atr.st_uid)->pw_name);
	buffcat(buff, " ");
	buffcat(buff, getgrgid(atr.st_gid)->gr_name);
	buffcat(buff, " ");
	time_cont(atr, buff, len);
	free(tmp);
}

static void	buff_cont(char *dir, char **lstcont, struct stat *atr, char **buff)
{
	char		*tmp;
	char		*tmp2;
	size_t		i;
	size_t		*len;

	buffcat(buff, "\n");
	len_ls(lstcont, atr, &len);
	i = 0;
	while (lstcont[i])
	{
		if (lstcont[i++][0] != 0)
		{
			tmp = ft_strjoin(dir, "/");
			tmp2 = ft_strjoin(tmp, lstcont[i - 1]);
			free(tmp);
			buff_cont2(tmp2, atr[i - 1], len, buff);
			buffcat(buff, " ");
			buff_link(atr[i - 1], buff, lstcont[i - 1], tmp2);
			buffcat(buff, lstcont[i - 1]);
			if (lstcont[i])
				buffcat(buff, "\n");
			free(tmp2);
		}
	}
	free(len);
}

void		buff_idir(char *opt, char *dir, char **lstcont, char **buff)
{
	struct stat	*atr;
	char		**cont;
	size_t		i;
	size_t		j;

	i = ((j = 0)) ? 0 : 0;
	while (lstcont[j])
		j++;
	cont = (char **)ft_memalloc(sizeof(char *) * (j + 1));
	while (lstcont[i])
		(cont[i] = ft_strdup(lstcont[i])) ? i++ : i++;
	if (ft_strchr(opt, '9') && ft_strcmp(dir, ".") != 0)
		buffcat(buff, dir);
	if (ft_strchr(opt, '9') && ft_strcmp(dir, ".") != 0)
		buffcat(buff, ":\n");
	buffcat(buff, "total ");
	buff_num(buff, block_size(opt, dir, cont));
	atr = (struct stat *)ft_memalloc(sizeof(struct stat) * (j + 1));
	set_pathdir(opt, dir, cont, atr);
	buff_cont(dir, cont, atr, buff);
	i = 0;
	while (cont[i])
		free(cont[i++]);
	free(cont);
	free(atr);
}
