#include "../header/minishell.h"

void	sigint(int sig)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

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

void	env(t_minishell *mini)
{
	ssize_t	i;

	i = -1;
	while (mini->env.raw_var[++i])
		if (mini->env.var_value[i])
			ft_putendl_fd(mini->env.raw_var[i], STDOUT_FILENO);
}

// void	print_export(t_minishell *mini)
// {
// 	ssize_t	i;
// 	t_env	env;
// 	char	*tmp;

// 	env = mini->env;
// 	i = -1;
// 	while (env.sorted[++i])
// 	{
// 		if (ft_strncmp(env.sorted[i], "_", 1))
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			tmp = ft_strchr(env.sorted[i], '=');
// 			write(1, env.sorted[i], tmp - env.sorted[i]);
// 			if (*(tmp + 1))
// 			{
// 				ft_putstr_fd("=\"", 1);
// 				ft_putstr_fd(tmp + 1, 1);
// 				ft_putendl_fd("\"", 1);
// 			}
// 			else
// 				ft_putendl_fd("", 1);
// 		}
// 	}
// }

int	add_var(t_minishell *mini, char **cmd)
{
	t_env	*env;
	char	**tmp;
	//char	*tmp2;
	ssize_t	i;

	env = &(mini->env);
	i = ft_str_str_len(env->raw_var);
	tmp = ft_duostrdup(env->raw_var, i + 1);
	if (!tmp)
		return (0);
	tmp[i] = cmd[1];
	free_env(env);
	if (!set_var(mini, tmp))
		return (0); //reset value
	return (1);
}

int	export(t_minishell *mini, char **cmd)
{
	if (ft_str_str_len(cmd) > 1)
		return (add_var(mini, cmd));
	// else
	// 	print_export(mini);
	return (1);
}

int	is_builtin(char **cmd, t_minishell *mini)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "env"))
		return (env(mini), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (exit(ft_atoi(cmd[1])), 1);
	if (!ft_strcmp(cmd[0], "export"))
		return (export(mini, cmd), 1);
	return (0);
}

void	execution(t_minishell *mini)
{
	t_lex	*lex;
	pid_t	pid;

	lex = mini->lex;
	while (lex)
	{
		//for if not 1 builtin
		pid = -2;
		//if should fork
		if (is_builtin(lex->cmd, mini) && pid != -2)
			exit (0);
		lex = lex->next;
	}
	
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	(void)env;
	ft_bzero(&mini, sizeof(mini));
	set_var(&mini, env);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN); //
		signal(SIGINT, sigint);
		//ft_bzero(&mini, sizeof(mini)); // still needed
		if (!my_read(&mini))
			return (free_env(&mini.env), 1);
		execution(&mini);
		lex_clear(&mini.lex, ft_free);
	}
}
