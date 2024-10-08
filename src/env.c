#include "../includes/minishell.h"

int	env(t_env *env)
{
	while (env)
	{
		if (ft_strchr(env->key, '?'))
		{
			env = env->next;
			continue ;
		}
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
	return (0);
}

t_env	*get_env_node(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp(key, temp->key, ft_strlen(key) + 1))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	insert_new_node(t_env *env, char *key, char *value)
{
	t_env	*temp;

	temp = env;
	while (temp->next)
		temp = temp->next;
	temp->next = make_new_env_node(key, value);
	if (!temp->next)
		return (0);
	return (1);
}

int	set_env_value(t_env *env, char *key, char *value)
{
	t_env	*target_node;
	char	*new_value;

	if (!key)
		return (0);
	target_node = get_env_node(env, key);
	if (!target_node)
		return (insert_new_node(env, key, value));
	if (value)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (0);
	}
	else
		new_value = NULL;
	if (target_node->value)
		free(target_node->value);
	target_node->value = new_value;
	return (1);
}

t_env	*load_envs(char *envp[])
{
	t_env	*env;
	char	**args;

	env = NULL;
	while (envp && *envp)
	{
		args = split_keyvalue(*envp++, '=');
		if (!args)
			return (NULL);
		if (!env)
		{
			env = make_new_env_node(args[0], args[1]);
			if (!env)
				return (NULL);
		}
		else if (!set_env_value(env, args[0], args[1]))
			return (NULL);
		free(args);
	}
	if (!set_env_value(env, ft_strdup("?"), ft_strdup("0")))
		return (NULL);
	if (!get_env_node(env, "OLDPWD"))
		if (!set_env_value(env, ft_strdup("OLDPWD"), NULL))
			return (NULL);
	return (env);
}
