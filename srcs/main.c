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
		// puts("hi");
		// printf("\"%s\"\t\"%s\"\t\"%s\"\n\n", env->raw_var[i], env->var_name[i], env->var_value[i]);
	}
	return (1);
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
			return (1);
		//signal(SIGINT, SIG_IGN);
		open("lol.tmp", __O_TMPFILE);
		lex_clear(&mini.lex, ft_free);
	}
}
