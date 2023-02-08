#include "ft_42sh.h"

void	fc_free(t_fc *fc)
{
	ft_strdel(&fc->ret_cmd);
	ft_arrclean(fc->filename);
}
