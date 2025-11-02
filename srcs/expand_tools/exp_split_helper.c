#include "../../header/minishell.h"

int	quotes2(char c, int *state)
{
	if (c == '"' && *state == DOUBLE)
		*state = 0;
	else if (c == '"' && *state != SINGLE && *state != DOUBLE)
		*state = DOUBLE;
	else if (c == '\'' && *state == SINGLE)
		*state = 0;
	else if (c == '\'' && *state != SINGLE && *state != DOUBLE)
		*state = SINGLE;
	return (0);
}

void	count_helper(char *in, ssize_t *i, int *q_s, int *prev)
{
	*prev = *q_s;
	while (in[(*i)] && (*prev) == (*q_s))
	{
		(*i)++;
		quotes2(in[(*i)], q_s);
	}
	(*prev) = (*q_s);
	if (in[(*i)])
		(*i)++;
}

void	count_helper2(char *in, ssize_t *i)
{
	ssize_t	j;

	j = 1;
	if (j == 1 && in[j + (*i)] == '?')
		j++;
	else
		while (in[(*i) + j] && is_valid_env(in[(*i) + j], j))
			j++;
	(*i) += j;
}

void	str_helper2(char **in, ssize_t *i)
{
	ssize_t	j;

	j = 1;
	if (j == 1 && (*in)[(*i) + j] == '?')
		j++;
	else
		while ((*in)[(*i) + j] && is_valid_env((*in)[(*i) + j], j))
			j++;
	(*i) += j;
}

void	str_helper1(char **in, ssize_t *i, int *q_s, int *prev_status)
{
	(*prev_status) = (*q_s);
	while ((*in)[(*i)] && (*prev_status) == (*q_s))
	{
		(*i)++;
		quotes2((*in)[(*i)], q_s);
	}
	(*prev_status) = (*q_s);
	if ((*in)[(*i)])
		(*i)++;
}
