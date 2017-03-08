/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:38:58 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/08 15:16:19 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		argcheck(char *dir, char **buff)
{
	struct stat		atr;

	if (lstat(dir, &atr) != 0 || stat(dir, &atr) != 0)
	{
		print_buff(buff);
		perror(dir);
	}
}

char		**arg_handle(char **opt, int ac, char **av)
{
	char		**lstdir;
	int			i[2];
	struct stat	atr;

	i[0] = 0;
	if ((i[1] = get_arg(opt, ac, av)) == -1)
		return (NULL);
	lstdir = (char **)ft_memalloc(sizeof(char *) * (ac - i[1] + 2));
	if (i[1] == ac)
		lstdir[0] = ft_strdup(".");
	while (i[1] < ac)
	{
		if (stat(av[i[1]++], &atr) != -1)
			lstdir[i[0]++] = ft_strdup(av[i[1] - 1]);
		else
		{
			ft_putstr_fd("ft_ls: ", 2);
			perror(av[i[1] - 1]);
			opt[0][ft_strlen(*opt)] = '9';
		}
	}
	if ((i[0] > 1 || ft_strchr(*opt, 'R') != NULL) && !ft_strchr(*opt, '9'))
		opt[0][ft_strlen(*opt)] = '9';
	return (lstdir);
}

int			get_arg(char **opt, int ac, char **av)
{
	int	i;

	i = 0;
	*opt = (char *)ft_memalloc(10);
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		if (av[i][1] == '-')
		{
			if (av[i][2] != '\0')
			{
				if (add_arg(opt, av[i]) == -1)
					return (-1);
			}
			else if (add_arg(opt, &av[i][1]) == -1)
				return (-1);
		}
		else if (add_arg(opt, av[i]) == -1)
			return (-1);
	}
	return (i);
}

void		check_add(char **opt, char op)
{
	if (ft_strchr(*opt, '1') && (op == 'C' || op == 'l')
			&& !ft_strchr(*opt, op))
		opt[0][ft_strlen_chr(*opt, '1')] = op;
	else if (ft_strchr(*opt, 'l') && (op == 'C' || op == '1')
			&& !ft_strchr(*opt, op))
		opt[0][ft_strlen_chr(*opt, 'l')] = op;
	else if (ft_strchr(*opt, 'C') && (op == '1' || op == 'l')
			&& !ft_strchr(*opt, op))
		opt[0][ft_strlen_chr(*opt, 'C')] = op;
	else if (op == 'f' && !ft_strchr(*opt, 'a'))
		opt[0][ft_strlen(*opt)] = 'a';
	else
		opt[0][ft_strlen(*opt)] = op;
}

int			add_arg(char **opt, char *op)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (j > 0 && op[++i] != '\0')
	{
		if (op[i] != 'l' && op[i] != 'R' && op[i] != 'a' && op[i] != 'S'
				&& op[i] != 'r' && op[i] != 't' && op[i] != '1'
				&& op[i] != 'C' && op[i] != 'f')
			j = -1;
	}
	if (j > 0)
	{
		j = 1;
		while (j < i)
			check_add(opt, op[j++]);
	}
	if (j < 0)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(op[i], 2);
		ft_putstr_fd("\nusage: ls [-CRaflrt1] [file ...]\n", 2);
	}
	return (j);
}
