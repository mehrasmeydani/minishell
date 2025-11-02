#include "../../header/minishell.h"

static int	has_valid_args(char **cmd)
{
	ssize_t	i;

	i = -1;
	while (cmd[++i] != NULL)
		if (i > 1)
			return (errno = E2BIG, 0);
	if (i != 2)
		return (errno = EINVAL, 0);
	return (1);
}

static int	export_pwd(t_minishell *mini, char *dir)
{
	char	*exporting[3];

	exporting[0] = ft_strdup("export");
	if (!exporting[0])
		return (0);
	exporting[1] = ft_strjoin("PWD=", dir);
	if (!exporting[1])
		return (free(exporting[0]), 0);
	exporting[2] = NULL;
	if (my_export(mini, exporting) != 1)
		return (free(exporting[0]), free(exporting[1]), 0);
	return (free(exporting[0]), free(exporting[1]), 1);
}

static int	export_oldpwd(t_minishell *mini, char *dir)
{
	char	*exporting[3];

	exporting[0] = ft_strdup("export");
	if (!exporting[0])
		return (0);
	exporting[1] = ft_strjoin("OLDPWD=", dir);
	if (!exporting[1])
		return (free(exporting[0]), 0);
	exporting[2] = NULL;
	if (my_export(mini, exporting) != 1)
		return (free(exporting[0]), free(exporting[1]), 0);
	return (free(exporting[0]), free(exporting[1]), 1);
}

static int	check_env_entry(char **var_name, bool ispwd)
{
	ssize_t	i;

	i = -1;
	while (var_name[++i] != NULL)
	{
		if (ispwd == true)
			if (!ft_strcmp(var_name[i], "PWD"))
				return (1);
		if (ispwd == false)
			if (!ft_strcmp(var_name[i], "OLDPWD"))
				return (1);
	}
	return (0);
}

int	cd(t_minishell *mini, char **cmd)
{
	char	*prevdir;
	char	*newdir;

	if (!has_valid_args(cmd))
		return (0);
	prevdir = getcwd(NULL, 0);
	if (!prevdir)
		return (0);
	if (chdir(cmd[1]) == -1)
		return (free(prevdir), 0);
	newdir = getcwd(NULL, 0);
	if (!newdir)
		return (free(prevdir), 0);
	if (check_env_entry(mini->env.var_name, true) == 1)
		if (!export_pwd(mini, newdir))
			return (free(prevdir), free(newdir), 0);
	if (check_env_entry(mini->env.var_name, false) == 1)
		if (!export_oldpwd(mini, prevdir))
			return (free(prevdir), free(newdir), 0);
	free(prevdir);
	free(newdir);
	return (1);
}
