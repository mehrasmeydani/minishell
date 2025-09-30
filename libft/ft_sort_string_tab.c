#include "../header/libft.h"

void	ft_swap(char **a, char **b)
{
	char	*why;

	why = *a;
	*a = *b;
	*b = why;
}
void	ft_sort_string_tab(char **tab)
{
	ssize_t		i;
	ssize_t		j;

	i = -1;
	while (tab[++i] && tab[i + 1])
	{
		j = i;
		while (tab[++j])
			if (0 < ft_strcmp(tab[i], tab[j]))
				ft_swap(&tab[i], &tab[j]);
	}
}
