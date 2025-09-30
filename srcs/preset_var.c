#include "../header/minishell.h"

int	preset_var(t_env *env)
{
	char	*tmp;

	env->raw_var = ft_calloc(5, sizeof(char *));
	if (!env->raw_var)
		return (0);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (ft_free(env->raw_var), 0);
	env->raw_var[0] = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!env->raw_var[0])
		return (ft_free(env->raw_var), 0);
	env->raw_var[1] = ft_strdup("SHLVL=0");
	if (!env->raw_var[1])
		return (ft_free(env->raw_var), 0);
	env->raw_var[2] = ft_strdup("_=./minishell");
	if (!env->raw_var[2])
		return (ft_free(env->raw_var), 0);
	env->raw_var[3] = ft_strdup("OLDPWD=");
	if (!env->raw_var[3])
		return (ft_free(env->raw_var), 0);
	return (1);
}
