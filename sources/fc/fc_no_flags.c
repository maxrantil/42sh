#include "ft_42sh.h"

int	fc_no_flags(t_fc *fc)
{
	if (fc->l == false \
		&& fc->r == false \
		&& fc->s == false \
		&& fc->e == 0 \
		&& fc->n == false)
		return (1);
	return (0);
}
