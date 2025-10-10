#include "../../header/minishell.h"

char *min_str(char **in)
{
	char	*out;
	ssize_t	i;

	out = *in;
	i = -1;
	while (in && in[++i])
		if (ft_strcmp(out, in[i]) > 0)
			out = in[i];
	return (out);
}

char *max_str(char **in)
{
	char	*out;
	ssize_t	i;

	out = *in;
	i = -1;
	while (in && in[++i])
		if (ft_strcmp(out, in[i]) < 0)
			out = in[i];
	return (out);
}

void	print_export2(char *str, t_env *env)
{
	ssize_t	i;

	i = -1;
	if (!strcmp("_", str))
		return ;
	while (++i < env->allocated_l)
	{
		if (!ft_strcmp(str, env->var_name[i]))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->var_name[i], 1);
			if (env->var_value[i])
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env->var_value[i], 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putendl_fd("", 1);
			break ;
		}
	}
}

void	print_export(t_minishell *mini)
{
	t_env	env;
	char	*print;
	char	*last;
	ssize_t	i;
	ssize_t	j;

	env = mini->env;
	print = min_str(env.var_name);
	print_export2(print, &env);
	last = print;
	i = -1;
	while (++i < env.allocated_l - 1)
	{
		j = -1;
		print = max_str(env.var_name);
		while (++j < env.allocated_l)
		{
			if (ft_strcmp(env.var_name[j], print) < 0 && ft_strcmp(env.var_name[j], last) > 0)
				print = env.var_name[j];
		}
		print_export2(print, &env);
		last = print;
	}
}

ssize_t	var_exists(t_env *env, char	*input, char *tmp)
{
	ssize_t	i;

	i = -1;
	while (++i < env->allocated_l)
	{
		if (!tmp && !ft_strcmp(input, env->var_name[i]))
			return (i);
		else if (tmp && !ft_strncmp(input, env->var_name[i], tmp - input))
			return (i);
	}
	return (-1);
}

int	add_var(t_minishell *mini, char **cmd)
{
	t_env	*env;
	char	**tmp;
	char	*tmp2;
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;

	env = &(mini->env);
	i = 0;
	while (cmd[++i])
	{
		tmp2 = ft_strchr(cmd[i], '=');
		k = var_exists(env, cmd[i], tmp2);
		if (!tmp2 && k != -1)
			return (1);
		else if (tmp2 && k != -1)
		{
			tmp = ft_duostrdup(env->raw_var, ft_str_str_len(env->raw_var));
			if (!tmp)
				return (0); // maybe free?
			tmp2 = ft_strdup(cmd[i]);
			if (!tmp2)
				return ft_free(tmp), (0); // maybe free?
			free(tmp[k]);
			tmp[k] = tmp2;
			free_env(env);
			if (!set_var(mini, tmp, 0))
				return (ft_free(tmp), 0);
			ft_free(tmp);
		}
		else
		{
			j = ft_str_str_len(env->raw_var);
			tmp = ft_duostrdup(env->raw_var, j + 1);
			if (!tmp)
				return (0); // maybe free?
			tmp[ft_str_str_len(env->raw_var)] = ft_strdup(cmd[i]);
			if (!tmp[ft_str_str_len(env->raw_var)])
				return (ft_free(tmp), 0);
			free_env(env);
			if (!set_var(mini, tmp, 0))
				return (ft_free(tmp), 0);
			ft_free(tmp);
		}
	}
	return (1);
}

int	export(t_minishell *mini, char **cmd)
{
	if (ft_str_str_len(cmd) > 1)
		return (add_var(mini, cmd));
	else
		print_export(mini);
	return (1);
}
