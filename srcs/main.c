/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:10:28 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 14:44:23 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	char		**lstdir;
	char		*buff;
	char		*opt;
	size_t		i;

	buff = (char *)ft_memalloc(2000);
	if (!(lstdir = arg_handle(&opt, ac, av)))
		return (-1);
	if (diropen(opt, lstdir, &buff) < 0)
		return (-1);
	i = 0;
	while (lstdir[i])
		free(lstdir[i++]);
	free(lstdir);
	free(opt);
	print_buff(&buff);
	free(buff);
	return (0);
}
