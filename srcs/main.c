#include "../header/minishell.h"

void	sigint(int sig)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

int	set_var(t_minishell *mini, char **env_var)
{
	t_env	*env;
	ssize_t	i;
	char	*tmp;
	int	lvl;

	(void)mini;
	env = &mini->env;
	i = ft_str_str_len(env_var);
	// if (!i)
	// 	return (preset_var(env));
	env->raw_var = ft_duostrdup(env_var, i);
	if (!env->raw_var)
		return (0);
	env->var_name = ft_calloc(i + 1, sizeof(char *));
	env->var_value = ft_calloc(i + 1, sizeof(char *));
	if (!env->var_value || !env->var_name)
		return (ft_free(env->var_name, i), free(env->var_value), free(env->raw_var)
		, 0);
	i = -1;
	while (env_var[++i])
	{
		tmp = ft_strchr(env_var[i], '=');
		env->var_name[i] = ft_substr(env_var[i], 0, tmp - env_var[i]);
		env->var_value[i] = ft_substr(env_var[i], tmp - env_var[i] + 1, ft_strlen(tmp) - 1);
		if (!env->var_value[i] || !env->var_name[i])
			return (ft_free(env->var_name, ft_str_str_len(env_var))
				, ft_free(env->var_value, i), ft_free(env->raw_var, i), 0);
		if (!ft_strcmp("SHLVL", env->var_name[i]))
		{
			lvl = ft_atoi(env->var_value[i]);
			lvl++;
			free(env->var_value[i]);
			env->var_value[i] = ft_itoa(lvl);
			if (!env->var_value[i])
				return (ft_free(env->var_name, ft_str_str_len(env_var))
					, ft_free(env->var_value, i), ft_free(env->raw_var, i), 0);
		}
	}
	return (1);
}

void	free_var(t_env *in)
{
	ft_free(in->raw_var, ft_str_str_len(in->raw_var));
	ft_free(in->var_name, ft_str_str_len(in->var_name));
	ft_free(in->var_value, ft_str_str_len(in->var_value));
}

void	env(t_minishell *mini)
{
	ssize_t	i;

	i = -1;
	while (mini->env.raw_var[++i])
		if (ft_strlen(mini->env.var_value[i]))
			ft_putendl_fd(mini->env.raw_var[i], STDOUT_FILENO);
}

int	is_builtin(char **cmd, t_minishell *mini)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "env"))
		return (env(mini), 1);
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
	while (true)
	{
		signal(SIGQUIT, SIG_IGN); //
		signal(SIGINT, sigint);
		ft_bzero(&mini, sizeof(mini));
		set_var(&mini, env);
		if (!my_read(&mini))
			return (free_var(&mini.env), lex_clear(&mini.lex, ft_free), 1);
		execution(&mini);
		//signal(SIGINT, SIG_IGN);
		free_var(&mini.env);
		open("lol.tmp", __O_TMPFILE);
		lex_clear(&mini.lex, ft_free);
	}
}
