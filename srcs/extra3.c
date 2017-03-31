#include "ft_ls.h"

void	diropenl(char **lstdir, char **buff, size_t **i, struct stat *atr)
{
	buffncat(buff, " ", (*i)[1]);
	buffcat(buff, lstdir[(*i)[0]]);
	buff_link(atr[(*i)[0]], buff, lstdir[(*i)[0]]);
	fill_nchar(buff, '\n', 1);
}

void	diropenc(char *opt, char **lstdir, char **buff, size_t **i)
{
	buffcat(buff, lstdir[(*i)[0]]);
	if (ft_strchr(opt, '1'))
		buffncat(buff, "\n", (*i)[1]);
	else
		buffncat(buff, " ", (*i)[1]);
}
