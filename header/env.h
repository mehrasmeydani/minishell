#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char	**raw_var;
	char	**var_name;
	char	**var_value;
	char	**var_pass_to_exec;
	char	**sorted;
}	t_env;


#endif