/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:35 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/05 11:07:08 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * add_var_to_env: Changes the envirement variable value if it already exists.
 * add a new variable if it doesn't exists.
 *
 * @arg: environment variable name and value.
 * @env: A pointer to the head of a linked list containing environment variables.
 */

void	add_var_to_env(char *arg, t_envp *env)
{
	char	*name;
	char	*value;
	char	*tname;
	char	*tvalue;

	tname = ft_substr(arg, 0, first_occur(arg, '='));
	tvalue = ft_substr(arg, first_occur(arg, '=') + 1, ft_strlen(arg));
	name = ft_strdup(tname);
	value = ft_strdup(tvalue);
	free(tname);
	free(tvalue);
	if (search_env_name(env, name) != NULL)
		change_env_value(&env, name, value);
	else
		addnode(&env, name, value);
	free(name);
	free(value);
}

/*
 * only_chars_nums: Checks if the string contails only characters
 * or number or = sign.
 * return: 1 if true.
 *	0 if not.
 */

int	only_chars_nums(char *arg)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_substr(arg, 0, first_occur(arg, '='));
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '=')
		{
			ft_printf(2,
				"Error: export: '%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

/*
 * empty_value: Updates or adds the envirement variable with no value.
 *
 * @env: A pointer to the head of a linked list containing environment variables.
 * @str: The envirement variable name and value.
 */

void	empty_value(t_envp *env, char *str)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(str, "=");
	if (!search_env(env, trimmed_str))
		addnode(&env, trimmed_str, "");
	else
		change_env_value(&env, trimmed_str, "");
	free(trimmed_str);
}

/*
 * export_variables: Processes and exports env.
 *
 * @args: Arguments passed to export.
 * @env: A pointer to the head of a linked list containing environment variables.
 */

void	export_variables(char **args, t_envp *env)
{
	while (*args)
	{
		if (!only_chars_nums(*args))
		{
			if (!(args + 1))
				break ;
			else
				args++;
		}
		if (count_char(*args, '=') == 0)
		{
			if (search_env_name(env, *args) != NULL)
				change_env_value(&env, *args, NULL);
			else
				addnode(&env, *args, NULL);
		}
		else if ((*args)[0] == '=')
			print_error("not a valid identifier");
		else if (count_char(*args, '=') == 1
			&& (*args)[ft_strlen(*args) - 1] == '=')
			empty_value(env, *args);
		else
			add_var_to_env(*args, env);
		args++;
	}
}

/*
 * export_: Manages and exports the environment variables
 * based on the provided arguments.
 *
 * Cases:
 *	export: lists all environment variables.
 *	export var=value: sets var to value, (visible in env and export).
 *	export var: sets var with no value (visible in export).
 *	export var=: sets var with empty string (visible in env and export).
 *	export =var: Error.
 * @env: A pointer to the head of linked list envirement variable.
 * @args: List of arguments passed to export.
 *
 * return: 0 on success.
 */

int	export_(t_envp *env, char **args)
{
	t_envp	*head;

	if (!args[0])
	{
		head = env;
		while (head)
		{
			if (!head->value)
				printf("declare -x %s\n", head->name);
			else
				printf("declare -x %s=\"%s\"\n", head->name, head->value);
			head = head->next;
		}
	}
	else
		export_variables(args, env);
	return (0);
}
