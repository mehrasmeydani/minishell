#include "../../header/minishell.h"

int	exit_helper(char *cmd)
{
	ssize_t	i;
	int		sign;
	ssize_t	sum;
	ssize_t	cmp;

	cmp = LONG_MAX;
	i = -1;
	sign = 1;
	sum = 0;
	while (ft_iswhitespace(cmd[++i]))
		;
	if ((cmd[i] == '-' || cmd[i] == '+') && (++i))
		if (cmd[i - 1] == '-')
			sign *= -1;
	if (!cmd[i])
		return (0);
	while (cmd[i] == '0')
		i++;
	if (ft_strlen(&cmd[i]) > 19 || (ft_strlen(&cmd[i]) == 19 && sign == -1
			&& ft_strcmp(&cmd[i], "9223372036854775808") > 0))
		return (0);
	while (cmd[i] && ft_isdigit(cmd[i]) && ++i)
		sum = sum * 10 + (cmd[i - 1] - '0');
	return (!(cmd[i] || (sum > cmp && sign == 1)));
}

void	builtin_exit(t_exec *exec, t_minishell *mini, char **cmd)
{
	ssize_t	i;
	ssize_t	j;

	j = ft_str_str_len(cmd);
	if (j == 1)
		return (close_exit(exec, mini, NULL, mini->error_code));
	i = -1;
	if (!exit_helper(cmd[1]))
		return (close_exit(exec, mini, NULL, 2));
	if (!cmd[1][0])
		return (close_exit(exec, mini, NULL, 2));
	if (j > 2)
		return (close_exit(exec, mini, NULL, 1));
	return (close_exit(exec, mini, NULL, (unsigned char)ft_atoi(cmd[1])));
}
