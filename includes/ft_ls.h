/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:35:10 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 17:42:49 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include <../libft/includes/libft.h>
# include <dirent.h>
# include <sys/stat.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <errno.h>

char	**arg_handle(char **opt, int ac, char **av);
int		get_arg(char **opt, int ac, char **av);
int		add_arg(char **opt, char *op);
int		diropen(char *opt, char **lstdir, char **buff);
int		dirlst(char *opt, char *dir, char **buff);
int		apply_sort(char *opt, char **lstdir);
int		sort_dir(char *opt, char **lstdir, char *path);
void	sort_size(char *opt, char **lstdir, char *path);
void	argcheck(char *dir, char **buff);
void	buff_dir(char *opt, char *dir, char **lstcont, char **buff);
void	buff_idir(char *opt, char *dir, char **lstcont, char **buff);
size_t	block_size(char *opt, char *dir, char **lstcont);
void	set_pathdir(char *opt, char *dir, char **lstcont, struct stat *atr);
size_t	print_buff(char **buff);
size_t	buffcat(char **buff, char *s);
size_t	buffncat(char **buff, char *s, size_t n);
char	*buff_perm(int i);
size_t	buff_num(char **buff, size_t i);
size_t	fill_nchar(char **buff, char c, size_t n);
char	file_type(mode_t mode);
char	*perm(int i);
void	time_cont(struct stat atr, char **buff, size_t *len);
void	buff_link(struct stat atr, char **buff, char *tmp);
int		dircheck(char *dir, char **buff);
void	tmp_free(char ***tmp);
void	buff_dir_name(char *opt, char *dir, char **buff);
int		buff_one(char *opt, char **lstcont, char **buff);
void	buff_permi(struct stat atr, char **buff);
void	searchdir2(char *opt, char *dir, char **lstcont, char **buff);
void	searchdir(char *opt, char *dir, char **lstcont, char **buff);
void	printfile_err(char **err, char **opt);
void	free_lst(char **lst);
int		print_err_perm(char **buff, char *dir);
void	len_ls(char **lstcont, struct stat *atr, size_t **len);
void	print_cont2(char *dir, struct stat atr, size_t *len, char **buff);
void	buff_cont2(char *dir, struct stat atr, size_t *len, char **buff);
void	diropenl(char **lstdir, char **buff, size_t **i, struct stat *atr);
void	diropenc(char *opt, char **lstdir, char **buff, size_t **i);

#endif
