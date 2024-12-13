/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:35 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:39 by mrezki           ###   ########.fr       */
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

void	add_var_to_env(char *arg, t_envp *env, int join_string)
{
	char	*name;
	char	*value;
	char	*tname;
	char	*tvalue;

	if (join_string)
		tname = ft_substr(arg, 0, first_occur(arg, '+'));
	else
		tname = ft_substr(arg, 0, first_occur(arg, '='));
	tvalue = ft_substr(arg, (unsigned int)first_occur(arg, '=') + 1, ft_strlen(arg));
	name = ft_strdup(tname);
	value = ft_strdup(tvalue);
	if (search_env_name(env, name) && join_string)
		append_to_env(&env, name, value);
	else if (search_env_name(env, name) && !join_string)
		change_env_value(&env, name, value);
	else
		addnode(&env, name, value);
}

/*
 * is_valid_identifier: Checks if the string contails only characters
 * or number or = sign.
 * return: 1 if true.
 *	0 if not.
 */

static int	is_valid_identifier(char *input, int *join_string)
{
	char	*str;
	size_t	i;
	int		err;

	i = 0;
	err = 0;
	if (count_char(input, '=') == 0 || input[0] == '=')
		str = input;
	else
		str = ft_substr(input, 0, first_occur(input, '='));
	*join_string = (str[ft_strlen(str) - 1] == '+');
	err = !(ft_isalpha(str[0]) || str[0] == '_');
	while (str[i])
	{
		if (!character_valid(str[i], i == ft_strlen(str) - 1,
				*join_string, input))
			err = 1;
		i++;	
	}
	if (err)
		ft_printf(2, "Error: export: '%s' is not a valid identifier\n", str);
	if (err)
		return (0);
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
	if (!search_env_name(env, trimmed_str))
		addnode(&env, trimmed_str, "");
	else
		change_env_value(&env, trimmed_str, "");
}

/*
 * export_variables: Adds, Updates or append the value of
 * the environment variable.
 *
 * @args: Arguments passed to export.
 * @env: A pointer to the head of a linked list containing environment variables.
 */

int	export_variables(char **args, t_envp *env, int *join_string)
{
	char	**tmp;
	int		err;

	tmp = args;
	err = 0;
	while (*args)
	{
		if (!is_valid_identifier(*args, join_string))
			err = 1;
		else if (count_char(*args, '=') == 0)
			add_empty(&env, *args);
		else if (count_char(*args, '=') == 1
			&& (*args)[ft_strlen(*args) - 1] == '='
			&& !join_string)
			empty_value(env, *args);
		else
			add_var_to_env(*args, env, *join_string);
		args++;
	}
	if (err)
		return (1);
	return (0);
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
 *	export var+=val2: Joins the value of var with val2.
 * @env: A pointer to the head of linked list envirement variable.
 * @args: List of arguments passed to export.
 *
 * return: 0 on success.
 */

int	export_(t_envp *env, char **args)
{
	int	join_string;

	join_string = 0;
	if (!args[0])
		print_export_vars(env);
	else
		return (export_variables(args, env, &join_string));
	return (0);
}
