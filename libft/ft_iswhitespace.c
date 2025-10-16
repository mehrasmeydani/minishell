#include "../header/libft.h"

int	ft_iswhitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}